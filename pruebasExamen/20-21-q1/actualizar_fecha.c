#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void Usage(char argv_1[]) {
    char buffer[64];

    sprintf(buffer, "Usage: %s file1...filen n <= 5\n", argv_1);
    write(1, buffer, strlen(buffer));
    exit(1);
}

void error_exit(char error[]) {
    char buffer[64];

    sprintf("Error on %s\n", error);
    write(1, buffer, strlen(buffer));

    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc > 6) {
        Usage(argv[0]);
    }

    int pids[argc - 1];

    for (int i = 1; i < argc; ++i) {
        int pid;
        if ((pid = fork()) < 0) {
            error_exit("fork");
        }
        
        else if (pid == 0) {
            execlp("touch", "touch", argv[i]);
            error_exit("execlp");
        }

        else {
            pids[i - 1] = pid;
        }
    }

    int pid;
    while ((pid = waitpid(0, NULL, 0)) > 0) {
        int pos;
        for (int i = 0; i < argc - 1; ++i) {
            if (pids[i] == pid) {
                pos = i;
            }
        }
        
        char buffer[64];

        sprintf(buffer, "Fecha %s actualizada por %d\n", argv[pos + 1], pids[pos]);
        write(1, buffer, strlen(buffer));
    }

    return 0;
}
