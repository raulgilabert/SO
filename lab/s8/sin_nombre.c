#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>


int main(int argc, char *argv[]) {
    // Elemento 0 es entrada, elemento 1 es salida
    int pipefd[2];

    if (pipe(pipefd) == -1) { // If error on creating pipe
        perror("Error creating pipe");

        exit(1);
    }

    int pid;

    if ((pid = fork()) < 0) {
        perror("Error on fork");
        exit(1);
    }

    if (pid == 0) {
        // Hijo
        close(0);

        dup(pipefd[0]);

        close(pipefd[0]);
        close(pipefd[1]);

        execlp("cat", "cat", (char*)NULL);

        perror("Error on execlp");
        exit(1);
    }
    if (pid > 0) {
        // Padre
        char buffer[16];
        sprintf(buffer, "Inicio\n");
        write(pipefd[1], buffer, strlen(buffer));

        //close(pipefd[1]);

        int exit_status;
        waitpid(pid, &exit_status, 0);

        sprintf(buffer, "Fin\n");
        write(1, buffer, strlen(buffer));
    }

    return 0;
}
