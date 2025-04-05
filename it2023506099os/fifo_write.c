#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *fifo_path = "/tmp/my_fifo"; // FIFO file path
    int fd;

    // Unlink and recreate FIFO in case it exists already
    unlink(fifo_path); // Remove any existing FIFO
    if (mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Open the FIFO for writing
    fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write a message to the FIFO
    const char *message = "Hello from the producer process!";
    if (write(fd, message, sizeof(message)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    printf("Message sent to FIFO: %s\n", message);

    // Close the FIFO
    close(fd);
    return 0;
}

