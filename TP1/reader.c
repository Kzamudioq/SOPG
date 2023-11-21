#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define READER_PROCESS_NAME "reader"
#define FIFO_NAME "TP_FIFO"
#define LOG_FILE "log.txt"
#define SIGNALS_FILE "signals.txt"
#define BUFFER_SIZE 300
#define LOG_PREFIX "DATA:"
#define SIGN_PREFIX "SIGN:"

// Function prototypes
static void exitHandler();
static void signalsHandler(int signo);
static int initializeSignalHandlers();
static void processInput(const char *buffer);

int main(void)
{
    char buffer[BUFFER_SIZE];
    int fifoDescriptor;

    // Register exit handler
    if (atexit(exitHandler) != 0)
    {
        fprintf(stderr, "[%s] Error registering exit handler.\n", READER_PROCESS_NAME);
        exit(EXIT_FAILURE);
    }

    // Initialize signal handlers
    if (initializeSignalHandlers() == -1)
    {
        exit(EXIT_FAILURE);
    }

    // Create named FIFO
    if (mkfifo(FIFO_NAME, S_IFIFO | 0666) != 0 && errno != EEXIST)
    {
        printf("[%s] mknod error %d (%s)\n", READER_PROCESS_NAME, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Open named FIFO
    fifoDescriptor = open(FIFO_NAME, O_RDONLY);
    if (fifoDescriptor < 0)
    {
        printf("[%s] Error opening FIFO %d (%s)\n", READER_PROCESS_NAME, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Open log files
    FILE *flog = fopen(LOG_FILE, "a");
    if (flog == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    FILE *fsign = fopen(SIGNALS_FILE, "a");
    if (fsign == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        ssize_t bytesRead;

        // Read from named FIFO
        if ((bytesRead = read(fifoDescriptor, buffer, sizeof(buffer))) <= 0)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Process received data
        processInput(buffer);
    }

    return 0;
}

// Exit handler function
static void exitHandler()
{
    printf("[%s] Attempt to close the files before exit.\n", READER_PROCESS_NAME);

    // Close files if they are open
    if (fclose(flog) != 0)
    {
        fprintf(stderr, "[%s] fclose error for file log.txt (%s)\n", READER_PROCESS_NAME, strerror(errno));
    }
    else
    {
        printf("[%s] File log.txt closed successfully.\n", READER_PROCESS_NAME);
    }

    if (fclose(fsign) != 0)
    {
        fprintf(stderr, "[%s] fclose error for file signals.txt (%s)\n", READER_PROCESS_NAME, strerror(errno));
    }
    else
    {
        printf("[%s] File signals.txt closed successfully.\n", READER_PROCESS_NAME);
    }

    printf("[%s] Exiting...\n", READER_PROCESS_NAME);
}

// Signal handler function for SIGINT
static void signalsHandler(int signo)
{
    write(1, "\nReceived SIGINT - User wants to quit application!\n", sizeof("\nReceived SIGINT - User wants to quit application!\n"));
    exit(EXIT_SUCCESS);
}

// Initialize signal handlers
static int initializeSignalHandlers()
{
    int ret = -1;
    struct sigaction sa;

    // Register exit handler
    if ((ret = atexit(exitHandler)) != 0)
    {
        fprintf(stderr, "[%s] atexit error %d\n", READER_PROCESS_NAME, ret);
        return ret;
    }

    sa.sa_handler = signalsHandler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    // For the reader process we only care about SIGINT signal (for the moment)
    if ((ret = sigaction(SIGINT, &sa, NULL)) != 0)
    {
        fprintf(stderr, "[%s] sigaction error for SIGINT %d (%s)\n", READER_PROCESS_NAME, errno, strerror(errno));
    }

    return ret;
}

// Process received input and write to files
static void processInput(const char *buffer)
{
    // Create a timestamp
    time_t currentTime;
    char timeBuffer[24] = {0};

    if (buffer == NULL)
    {
        printf("[%s] Received NULL buffer. Returning...\n", READER_PROCESS_NAME);
        return;
    }

    // Format the time using strftime
    time(&currentTime);
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localtime(&currentTime));

    if (strncmp(buffer, LOG_PREFIX, sizeof(LOG_PREFIX) - 1) == 0)
    {
        // Don't write the prefix for DATA messages
        fprintf(flog, "[%s] %s\n", timeBuffer, buffer + sizeof(LOG_PREFIX) - 1);
        fflush(flog);
    }
    else if (strncmp(buffer, SIGN_PREFIX, sizeof(SIGN_PREFIX) - 1) == 0)
    {
        // For signal messages store the full message
        fprintf(fsign, "[%s] %s\n", timeBuffer, buffer);
        fflush(fsign);
    }
    else
    {
        printf("[%s] The buffer does not have a recognized prefix.\n", READER_PROCESS_NAME);
    }
}
