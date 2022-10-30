#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void Usage(char nombre[]) {
    char buffer[512];
    sprintf(buffer,
        "Se debe de ejecutar así %s archivo1 ... archivon siendo n máximo 10\n"
        , nombre);
    write(1, buffer, strlen(buffer));
    exit(1);
}


int main(int argc, char *argv[]) {
    if ((argc < 2 || argc > 11))
        Usage(argv[0]);

    int pids[argc - 1];

    for (int i = 0; i  < argc - 1; ++i) {
        
    } 
}

