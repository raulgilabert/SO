#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>

void error_exit(char *msg, int exit_status) {
    perror(msg);
    exit(exit_status);
}


int main(int argc, char *argv[]) {
    int pid;

    if ((pid = fork()) < 0) error_exit("Error en fork", 1);

    char buffer[64];

    switch (pid) {
	case 0: // Es el hijo
	    sprintf(buffer, "PID: %d; parámetro: %s\n", getpid(), argv[1]);
	    write(1, buffer, strlen(buffer));
	    break;
	default:
	    sprintf(buffer, "PID: %d\n", getpid());
	    write(1, buffer, strlen(buffer));
    }

    while (1);

    return 0;
}
