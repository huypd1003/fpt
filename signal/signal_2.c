#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void print_signal_name(int signal) {
    switch (signal) {
        case SIGHUP:   printf("SIGHUP\n");   break;
        case SIGINT:   printf("SIGINT\n");   break;
        case SIGQUIT:  printf("SIGQUIT\n");  break;
        case SIGILL:   printf("SIGILL\n");   break;
        case SIGABRT:  printf("SIGABRT\n");  break;
        case SIGFPE:   printf("SIGFPE\n");   break;
        case SIGKILL:  printf("SIGKILL\n");  break;
        case SIGSEGV:  printf("SIGSEGV\n");  break;
        case SIGPIPE:  printf("SIGPIPE\n");  break;
        case SIGALRM:  printf("SIGALRM\n");  break;
        case SIGTERM:  printf("SIGTERM\n");  break;
        case SIGUSR1:  printf("SIGUSR1\n");  break;
        case SIGUSR2:  printf("SIGUSR2\n");  break;
        case SIGCHLD:  printf("SIGCHLD\n");  break;
        case SIGCONT:  printf("SIGCONT\n");  break;
        case SIGSTOP:  printf("SIGSTOP\n");  break;
        case SIGTSTP:  printf("SIGTSTP\n");  break;
        case SIGTTIN:  printf("SIGTTIN\n");  break;
        case SIGTTOU:  printf("SIGTTOU\n");  break;
        case SIGBUS:   printf("SIGBUS\n");   break;
        case SIGPOLL:  printf("SIGPOLL\n");  break;
        case SIGPROF:  printf("SIGPROF\n");  break;
        case SIGSYS:   printf("SIGSYS\n");   break;
        case SIGTRAP:  printf("SIGTRAP\n");  break;
        case SIGURG:   printf("SIGURG\n");   break;
        case SIGVTALRM:printf("SIGVTALRM\n");break;
        case SIGXCPU:  printf("SIGXCPU\n");  break;
        case SIGXFSZ:  printf("SIGXFSZ\n");  break;

        default:       printf("Unknown signal %d\n", signal); break;
    }
}

void print_blocked_signals() {
    sigset_t blocked_signals;
    sigemptyset(&blocked_signals);
    if (sigprocmask(SIG_SETMASK, NULL, &blocked_signals) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("Signals blocked:\n");
    for (int sig = 1; sig < 32; sig++) {
        if (sigismember(&blocked_signals, sig)) {
            print_signal_name(sig);
        }
    }
}

int main() {
    sigset_t signal_set;

    sigemptyset(&signal_set);
    sigaddset(&signal_set, SIGINT);
    sigaddset(&signal_set, SIGABRT);
    sigprocmask(SIG_BLOCK, &signal_set, NULL);

    print_blocked_signals();

    return 0;
}
