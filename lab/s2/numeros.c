#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE 8 // longitud máxima


int
esNumero (char *str)
{
    if (str == NULL) // Puntero nulo -> no es número
	return 0;

    if (str[0] == '-') // Si es un posible número negativo se avanza una
		       // posición el puntero
	++str;

    int i;

    for (i = 0; str[i] != '\0'; ++i)
	if ( str[i] < '0' || str[i] > '9') // El char no es un número
	    return 0;

    if (i > MAX_SIZE) // Se supera el tamño máximo
	return 0;

    return i > 0; // En caso de que no esté vacío
}



int
main (int argc, char *argv[])
{
    char buffer[128];

    for (int i = 1; i < argc; ++i) // Se salta el argumento 0 que es el nombre
				   // del ejecutable
    {
	if (esNumero(argv[i]) == 1)
	    sprintf(buffer, "El argumento %s en la posición %d es un número de 8 cifras o menos\n", argv[i], i);
	else
	    sprintf(buffer, "El argumento %s en la posición %d es nulo, no es un número o es de más de 8 cifras\n", argv[i], i);

	write(1, buffer, strlen(buffer));
    }
}
