#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    signal(SIGINT,SIG_IGN);
    struct sigaction sa;
    sigaction(SIGINT, NULL, &sa);
    while (1)
    {
        if (sa.sa_handler == SIG_IGN) {
        signal(SIGINT,SIG_DFL);
        printf("Signal %d is being ignored.\n", SIGINT);

    } 
    }
    return 0;
}