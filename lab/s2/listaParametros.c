#include <stdio.h>
#include <unistd.h>
#include <string.h>

void Usage() {
    char buff[128];
    sprintf(buff, "Usage:listaParametros arg1 [arg2..argn]\nEste programa escribe por su salida la lista de argumentos que recibe\n");
    write(1, buff, strlen(buff));
}

int main(int argc,char *argv[])
{
    char buf[80];
    
    if (argc > 1) {
	for (int i=0;i<argc;i++){
	    sprintf(buf,"El argumento %d es %s\n",i,argv[i]);
	    write(1,buf,strlen(buf));
	}
    } else {
	Usage();
    }
    return 0;
}
