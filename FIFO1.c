#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    char buf[100], buf1[100];
    int fd, fd1, i = 0;

    // Create FIFO2
    mkfifo(FIFO2, 0666);

    printf("\nEnter the string : \n");

    // Read a string until a newline or a newline + '#' is encountered
    while (1) {
        char str = getchar();
        if (str == '\n' || (i > 0 && buf[i - 1] == '\n' && str == '#')) {
            buf[i] = '\0';  // Null-terminate the string
            break;
        }
        buf[i++] = str;
    }

    mkfifo(FIFO1, 0666);
    fd = open(FIFO1, O_WRONLY);
    write(fd, buf, strlen(buf));
    fflush(stdout);  // Flush standard output
    printf("\nMessage sent");
    fflush(stdout);  // Flush standard output
    close(fd);

    fd1 = open(FIFO2, O_RDONLY);
    read(fd1, buf1, sizeof(buf1));
    printf("\n\nMessage received: %s", buf1);
    fflush(stdout);  // Flush standard output
    close(fd1);

    return 0;
}

