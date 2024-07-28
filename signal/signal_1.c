#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void signal_sigint(){
    printf("can't out\n");
}
int main()
{
	signal(SIGINT, signal_sigint);
    while (1) {
        sleep(1);
    }
    return 0;
}
