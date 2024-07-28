#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd, bytes;
    unsigned char data[3];

    const char *pDevice = "/dev/input/mice";
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }

    int left, middle, right;
    signed char x, y;
    while(1)
    {
        // Read Mouse     
        bytes = read(fd, data, sizeof(data));

        if(bytes > 0)
        {
            left = data[0] & 0x1;
            right = (data[0] & 0x2) > 0;
            middle = (data[0] & 0x4) > 0;

            x = data[1];
            y = data[2];
            printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", x, y, left, middle, right);
        }
        else
        {
            perror("Failed to read mouse data");
            break;
        }
    }

    close(fd);
    return 0; 
}
