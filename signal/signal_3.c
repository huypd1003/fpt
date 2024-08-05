#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    sigset_t sigset;

    // block sigint
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigprocmask(SIG_BLOCK, &sigset, NULL);
    printf("SIGINT is blocked...\n");
    sleep(5);

    sigset_t pending;
    if (sigpending(&pending) == -1) {
        perror("sigpending");
        return 1;
    }
    if (sigismember(&pending, SIGINT)) {
        printf("SIGINT is in the pending signals. Exiting program.\n");
        exit(0);
    } else {
        printf("SIGINT is not in the pending signals.\n");
    }
    // SIG_UNBLOCK
    if (sigprocmask(SIG_UNBLOCK, &sigset, NULL) == -1) {
        perror("sigprocmask");
        return 1;
    }
    while (1) {
        pause();
    }

    return 0;
}
