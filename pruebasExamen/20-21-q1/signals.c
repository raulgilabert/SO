#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void Usage(char argv_1[]) {
    char buffer[64];

    sprintf(buffer, "Usage: %s N being 0 < N <= 10\n", argv_1);
    write(1, buffer, strlen(buffer));
    exit(1);
}

void error_exit(char error[]) {
    char buffer[64];

    sprintf("Error on %s\n", error);
    write(1, buffer, strlen(buffer));

    exit(1);
}

void f_signals(int s) {
    if (s == SIGALRM) {
        char buffer[64];
        sprintf(buffer, "%d: Timeout\n", getpid());
        write(1, buffer, strlen(buffer));

        exit(0);
    }
    else if (s == SIGUSR1) {
        exit(alarm(0));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2 || atoi(argv[1]) <= 0 || atoi(argv[1]) > 10) {
        Usage(argv[0]);
    }

    int num = atoi(argv[1]);
  
    sigset_t mask;
    struct sigaction sa;
    
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    sa.sa_mask = mask;
    sa.sa_flags = 0;
    sa.sa_handler = f_signals;

    sigaction(SIGALRM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    for (int i = 0; i < num; ++i) {
       int pid;
        if ((pid = fork()) < 0) {
            error_exit("fork");
        }

        if (pid == 0) {
            sigprocmask(SIG_SETMASK, &mask, NULL);

            sigfillset(&mask);
            sigdelset(&mask, SIGALRM);
            sigdelset(&mask, SIGUSR1);
            alarm(3);

            sigsuspend(&mask);
        }
        else {
            if (pid % 2 == 0) {
                kill(pid, SIGUSR1);
            }
        }
    }

    int info, pid;
    while ((pid = waitpid(0, &info, 0)) > 0) {
        if (WIFEXITED(info) && pid%2 == 0) {
            char buffer[64];

            sprintf(buffer, "Hijo %d. Segundos restantes %d\n", pid,
                    WEXITSTATUS(info));
            write(1, buffer, strlen(buffer));
        }
    }

    return 0;
}
