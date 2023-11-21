#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define FIFO_NAME "myfifo"
#define LOG_FILE "log.txt"
#define SIGNALS_FILE "signals.txt"
#define BUFFER_SIZE 300

static FILE *flog = NULL;
static FILE *fsign = NULL;

// Prototipos de funciones
static void exitHandler();
static void signalsHandler(int signo);
static int initializeSignalHandlers();
static void processInput(const char *buffer);

int main(void)
{
    char buffer[BUFFER_SIZE];
    int fifoDescriptor;

    // Crear o abrir el named fifo
    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        if (errno != EEXIST)
        {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    // Abrir el named fifo
    printf("Waiting for data...\n");
    if ((fifoDescriptor = open(FIFO_NAME, O_RDONLY)) == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Configurar manejador de señales
    if (initializeSignalHandlers() != 0)
    {
        exit(EXIT_FAILURE);
    }

    // Abrir archivos de log
    flog = fopen(LOG_FILE, "a");
    if (flog == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fsign = fopen(SIGNALS_FILE, "a");
    if (fsign == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Bucle principal
    while (1)
    {
        ssize_t bytesRead;

        // Leer desde el named fifo
        if ((bytesRead = read(fifoDescriptor, buffer, sizeof(buffer))) <= 0)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Manejar la señal recibida
        processInput(buffer);
    }

    return 0;
}

// Función para manejar señales
static void signalsHandler(int signo)
{
    printf("\nReceived SIGINT - User wants to quit application!\n");
    exitHandler();
}

// Función para manejar la señal de salida
static void exitHandler()
{
    printf("Attempt to close the files before exit.\n");

    // Cerrar archivos si están abiertos
    if (flog != NULL)
    {
        if (fclose(flog) != 0)
        {
            fprintf(stderr, "fclose error for file %s (%s)\n", LOG_FILE, strerror(errno));
        }
        else
        {
            printf("File %s closed successfully.\n", LOG_FILE);
        }
    }

    if (fsign != NULL)
    {
        if (fclose(fsign) != 0)
        {
            fprintf(stderr, "fclose error for file %s (%s)\n", SIGNALS_FILE, strerror(errno));
        }
        else
        {
            printf("File %s closed successfully.\n", SIGNALS_FILE);
        }
    }

    printf("Exiting...\n");
    exit(EXIT_SUCCESS);
}

// Función para manejar señales y cerrar archivos antes de salir
static int initializeSignalHandlers()
{
    int ret = -1;
    struct sigaction sa;

    // Registrar un manejador para la llamada exit()
    if ((ret = atexit(exitHandler)) != 0)
    {
        fprintf(stderr, "atexit error %d\n", ret);
        return ret;
    }

    sa.sa_handler = signalsHandler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    // Para el proceso lector solo nos importa la señal SIGINT (por el momento)
    if ((ret = sigaction(SIGINT, &sa, NULL)) != 0)
    {
        fprintf(stderr, "sigaction error for SIGINT %d (%s)\n", errno, strerror(errno));
    }

    return ret;
}

// Función para procesar la entrada y escribir en archivos
static void processInput(const char *buffer)
{
    // Crear una marca de tiempo, solo por diversión
    time_t currentTime;
    char timeBuffer[24] = {0};

    if (buffer == NULL)
    {
        printf("Received NULL buffer. Returning...\n");
        return;
    }

    // Formatear el tiempo usando strftime
    time(&currentTime);
    strftime(timeBuffer, sizeof(timeBuffer), "[%Y-%m-%d %H:%M:%S] ", localtime(&currentTime));

    if (strncmp(buffer, "DATA:", sizeof("DATA:") - 1) == 0)
    {
        // Decision estética: no escribir el prefijo para los mensajes DATA, por lo tanto, el desplazamiento del búfer
        fprintf(flog, "%s%s\n", timeBuffer, buffer + sizeof("DATA:") - 1);
        fflush(flog);
    }
    else if (strncmp(buffer, "SIGN:", sizeof("SIGN:") - 1) == 0)
    {
        // Para los mensajes de señales es más bonito almacenar el mensaje completo
        fprintf(fsign, "%s%s\n", timeBuffer, buffer);
        fflush(fsign);
    }
    else
    {
        printf("The buffer does not have a recognized prefix.\n");
    }
}
