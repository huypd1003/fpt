#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Vui lòng nhập tên tệp và tên thư mục.\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Không tồn tại tệp cần sao chép");
        return 1;
    }

    char buffer[100];
    ssize_t a = read(fd, buffer, sizeof(buffer));
    if (a == -1) {
        perror("Đọc tệp không thành công");
        close(fd);
        return 1;
    }
    close(fd);

    char *filename = strrchr(argv[1], '/');
    filename = filename ? filename + 1 : argv[1];

    char output[100];
    snprintf(output, sizeof(output), "%s/%s", argv[2], filename);

    int fd1 = open(output, O_CREAT | O_RDWR, 0666);
    if (fd1 == -1) {
        perror("Đường dẫn sai");
        return 1;
    }

    if (write(fd1, buffer, a) == -1) {
        perror("Ghi tệp không thành công");
        close(fd1);
        return 1;
    }
    close(fd1);

    printf("Sao chép thành công đến %s\n", output);
    return 0;
}
