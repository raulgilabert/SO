#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

void error_exit(char *msg, int exit_status) {
    perror(msg);
    exit(exit_status);
}


void muta_a_ps(char *username) {
    execlp("ps", "ps", "-u", username, (char*)NULL);
    error_exit("Ha fallado la mutación al ps", 1);
}


int main(int argc, char *argv[]) {
    int pid;

    char buffer[64];

    for (int i = 1; i < argc; ++i) {
	if ((pid = fork()) < 0) error_exit("Error en fork", 1);

	switch (pid) {
	    case 0:
		sprintf(buffer, "Argumento: %s\n", argv[i]);
		write(1, buffer, strlen(buffer));

		muta_a_ps(argv[i]);
		break;

	    default:
		waitpid(pid, NULL, 0);
	}
    }

    return 0;
}
