#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *fifo_path = "/tmp/my_fifo"; // FIFO file path
    int fd;
    char buffer[128]; // Buffer to store the received message

    // Open the FIFO for reading
    fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read data from the FIFO
    if (read(fd, buffer, sizeof(buffer)) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    printf("Received message: %s\n", buffer);

    // Close the FIFO
    close(fd);
    return 0;
}

