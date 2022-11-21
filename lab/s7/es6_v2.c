#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

void tract_sigint() {
	char buff[256];
	sprintf(buff,"signal rebut\n");
	write(1,&buff,strlen(buff));
}

int main() {
	struct sigaction sa;
	sa.sa_handler = &tract_sigint;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);
	sigaction(SIGINT,&sa,NULL);

	char c;
	char buff[256];
	int ret = read(0, &c, sizeof(char));
	if (ret >= 0) {
		sprintf(buff,"read correct0\n");
		write(1,buff,strlen(buff));
	} else {
		if (errno == EINTR) sprintf(buff,"read interrumpido por signal\n");
		else sprintf(buff,"read error\n");
		write(1,buff,strlen(buff));
	}
}
