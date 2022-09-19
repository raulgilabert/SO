#include "mis_funciones.h"

int main (int argc, char *argv[]) {
    char buffer[128];
    int i;

    int suma = 0;

    for (i = 1; i < argc; ++i) // Se salta el argumento 0 que es el nombre
				   // del ejecutable
    {
	if (esNumero(argv[i]) == 0) {
	    sprintf(buffer, "Error: el parámetro \"%s\" no es un número\n", argv[i]);
	    write(1, buffer, strlen(buffer));
	    return 0;
	}

	suma += mi_atoi(argv[i]);
    }

    sprintf(buffer, "La suma es %d\n", suma);
    write(1, buffer, strlen(buffer));
    return 0;
}
