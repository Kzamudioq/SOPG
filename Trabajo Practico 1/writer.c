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

FILE *flog; // Archivo de registro
int fd;    // Descriptor de archivo FIFO

// Función de manejo de errores
void handleError(const char *message, int exitCode)
{
    perror(message);
    exit(exitCode);
}

// Manejador de señales para SIGUSR1 y SIGUSR2
void signalsHandler(int signo);

// Manejador de salida para cerrar archivos y descriptores antes de salir
void exitHandler();

// Inicializa los manejadores de señales y archivos de registro
void initializeSignalHandlers();

int main(void)
{
    char outputBuffer[BUFFER_SIZE];
    int32_t bytesWrote;

    // Inicializar manejadores de señales y abrir archivo de registro
    initializeSignalHandlers();

    // Crear archivo de registro
    flog = fopen("log.txt", "a");

    if (!flog)
    {
        handleError("Error al abrir archivo de registro", EXIT_FAILURE);
    }

    // Crear named fifo. No hace nada si ya existe
    if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1 && errno != EEXIST)
    {
        handleError("Error creando named fifo", EXIT_FAILURE);
    }

    // Abrir named fifo. Bloquea hasta que otro proceso lo abre
    printf("Esperando lectores...\n");
    if ((fd = open(FIFO_NAME, O_WRONLY)) == -1)
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

        // Eliminar el carácter de nueva línea
        size_t len = strlen(outputBuffer);
        if (len > 0 && outputBuffer[len - 1] == '\n')
        {
            outputBuffer[len - 1] = '\0';
        }

        // Escribir el buffer en named fifo con el formato correcto
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

// Manejador de señales para SIGUSR1 y SIGUSR2
void signalsHandler(int signo)
{
    char signalMessage[8];
    // Formato de mensaje: SIGN:1 o SIGN:2
    snprintf(signalMessage, sizeof(signalMessage), "SIGN:%d", (signo == SIGUSR1) ? 1 : 2);

    // Escribir la señal en named fifo con el formato correcto
    if (write(fd, signalMessage, strlen(signalMessage)) == -1)
    {
        perror("write");
    }

    // Escribir la señal en el archivo de registro con la hora de registro
    time_t currentTime;
    char timeBuffer[24] = {0};
    time(&currentTime);
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localtime(&currentTime));
    fprintf(flog, "%s %s\n", timeBuffer, signalMessage);
}

// Manejador de salida para cerrar archivos y descriptores antes de salir
void exitHandler()
{
    printf("Intentando cerrar los archivos y descriptores antes de salir.\n");

    // Cerrar named fifo
    unlink(FIFO_NAME);

    // Cerrar descriptor de archivo FIFO
    close(fd);

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

    printf("Saliendo...\n");
    exit(EXIT_SUCCESS);
}

// Inicializa los manejadores de señales y archivos de registro
void initializeSignalHandlers()
{
    // Registrar el manejador de señales SIGUSR1 y SIGUSR2
    signal(SIGUSR1, signalsHandler);
    signal(SIGUSR2, signalsHandler);

    // Registrar el manejador de salida
    if (atexit(exitHandler) != 0)
    {
        handleError("Error al registrar el manejador de salida", EXIT_FAILURE);
    }
}
