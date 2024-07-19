#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[]){

        if (argc != 3) {
                printf("vui long nhap ten file va ten thu muc ");
        return 1;
}
        int fd = open (argv[1], O_RDONLY);
        if (fd == -1){
                perror("khong ton tai thu muc can sao chep");
        }
        char buffer[100];
        ssize_t a;
        a=read(fd, buffer,sizeof(buffer));

        char *string1 = argv[1];
        char *string2 = argv[2];
        char output[100];
        strcpy(output,string2);
        strcat(output, string1);
        printf("%s",output);
	int fd1 = open(output, O_CREAT|O_RDWR);
        if (fd1 == -1){
                perror("duong dan sai");
        }
        int text= write (fd1 , buffer, a);
        return 0;
}

