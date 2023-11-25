#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <time.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 300

FILE *flog, *fsign; // Archivos de registro

// Función de manejo de errores
void handleError(const char *message, int exitCode)
{
    perror(message);
    exit(exitCode);
}

// Manejador de señales para SIGINT
void signalsHandler(int signo);

// Manejador de salida para cerrar archivos antes de salir
void exitHandler();

// Inicializa los manejadores de señales y archivos de registro
void initializeSignalHandlers();

// Procesa la entrada recibida del FIFO y escribe en archivos de registro
void processInput(const char *buffer);

int main(void)
{
    char outputBuffer[BUFFER_SIZE];
    uint32_t bytesWrote;
    int32_t returnCode, fd;

    // Inicializar manejadores de señales y abrir archivos de registro
    initializeSignalHandlers();

    // Crear archivos de registro
    flog = fopen("log.txt", "a");
    fsign = fopen("signals.txt", "a");

    if (!flog || !fsign)
    {
        handleError("Error al abrir archivos de registro", EXIT_FAILURE);
    }

    // Crear named fifo. No hace nada si ya existe
    if ((returnCode = mknod(FIFO_NAME, S_IFIFO | 0666, 0)) != -1)
    {
        handleError("Error creando named fifo", EXIT_FAILURE);
    }

    // Abrir named fifo. Bloquea hasta que otro proceso lo abre
    printf("Esperando lectores...\n");
    if ((fd = open(FIFO_NAME, O_WRONLY)) < 0)
    {
        handleError("Error abriendo archivo named fifo", EXIT_FAILURE);
    }

    // Llamadas al sistema abiertas sin error -> otro proceso adjunto a named fifo
    printf("Hay un lector, escribe algo...\n");

    // Bucle infinito
    while (1)
    {
        // Obtener texto desde la consola
        fgets(outputBuffer, BUFFER_SIZE, stdin);

        // Manejar señales (Ctrl+C)
        signalsHandler(SIGINT);

        // Escribir el buffer en named fifo. Strlen para incluir el carácter de nueva línea
        if ((bytesWrote = write(fd, outputBuffer, strlen(outputBuffer))) == -1)
        {
            perror("write");
        }
        else
        {
            printf("Escritor: escribió %d bytes\n", bytesWrote);
        }
    }

    return 0;
}

// Manejador de señales para SIGINT
void signalsHandler(int signo)
{
    if (signo == SIGINT)
    {
        printf("\nRecibida la señal SIGINT - El usuario quiere salir de la aplicación.\n");
        exitHandler();
    }
}

// Manejador de salida para cerrar archivos antes de salir
void exitHandler()
{
    printf("Intentando cerrar los archivos antes de salir.\n");

    if (flog != NULL)
    {
        if (fclose(flog) != 0)
        {
            perror("Error al cerrar el archivo de registro");
        }
        else
        {
            printf("log.txt cerrado correctamente.\n");
        }
    }

    if (fsign != NULL)
    {
        if (fclose(fsign) != 0)
        {
            perror("Error al cerrar el archivo de señales");
        }
        else
        {
            printf("signals.txt cerrado correctamente.\n");
        }
    }

    printf("Saliendo...\n");
    exit(EXIT_SUCCESS);
}

// Inicializa los manejadores de señales y archivos de registro
void initializeSignalHandlers()
{
    // Registrar el manejador de salida
    if (atexit(exitHandler) != 0)
    {
        handleError("Error al registrar el manejador de salida", EXIT_FAILURE);
    }

    // Configurar el manejador de señales SIGINT
    struct sigaction sa;
    sa.sa_handler = signalsHandler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) != 0)
    {
        handleError("Error al configurar el manejador de señales SIGINT", EXIT_FAILURE);
    }
}

// Procesa la entrada recibida del FIFO y escribe en archivos de registro
void processInput(const char *buffer)
{
    time_t currentTime;
    char timeBuffer[24] = {0};

    if (buffer == NULL)
    {
        fprintf(stderr, "Error: Se recibió un buffer nulo\n");
        return;
    }

    time(&currentTime);
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S ", localtime(&currentTime));

    if (strncmp(buffer, "DATA:", 5) == 0)
    {
        // Extraer y registrar datos en log.txt
        fprintf(flog, "%s %s\n", timeBuffer, buffer + 5);
    }
    else if (strncmp(buffer, "SIGN:", 5) == 0)
    {
        // Extraer y registrar señal en signals.txt
        fprintf(fsign, "%s %s\n", timeBuffer, buffer + 5);
    }
}