#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, " %s <file path>\n", argv[0]);
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }
    close(fd);
    return 0;
}