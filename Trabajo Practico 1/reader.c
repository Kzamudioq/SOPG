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

// Manejador de salida para cerrar archivos antes de salir
void exitHandler();

// Inicializa los manejadores de señales y archivos de registro
void initializeSignalHandlers();

// Procesa la entrada recibida del FIFO y escribe en archivos de registro
void processInput(const char *buffer);

int main(void)
{
    uint8_t inputBuffer[BUFFER_SIZE];
    uint32_t bytesRead;

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
    if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1 && errno != EEXIST)
    {
        handleError("Error creando named fifo", EXIT_FAILURE);
    }

    // Abrir named fifo. Bloquea hasta que otro proceso lo abre
    printf("Esperando escritores...\n");
    int fd = open(FIFO_NAME, O_RDONLY);

    if (fd == -1)
    {
        handleError("Error abriendo archivo named fifo", EXIT_FAILURE);
    }

    // Llamadas al sistema abiertas sin error -> otro proceso adjunto a named fifo
    printf("Hay un escritor\n");

    // Bucle hasta que la llamada de lectura devuelva un valor <= 0
    while ((bytesRead = read(fd, inputBuffer, BUFFER_SIZE)) > 0)
    {
        inputBuffer[bytesRead] = '\0';
        printf("Lector: leídos %d bytes: \"%s\"\n", bytesRead, inputBuffer);

        // Procesar la entrada y escribir en archivos de registro
        processInput((const char *)inputBuffer);
    }

    // Cerrar archivos y salir
    exitHandler();

    return 0;
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
    else
    {
        // Registrar texto en log.txt
        fprintf(flog, "%s %s\n", timeBuffer, buffer);
    }
}
