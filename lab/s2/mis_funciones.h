#ifndef MIS_FUNCIONES
#define MIS_FUNCIONES

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE 8 // longitud máxima

// Convierte un char a número
unsigned int char2int(char c);

// Convierte un string (array de chars) en un entero
int mi_atoi(char *s);

// Comprueba si el string es un número
int esNumero (char *str);

#endif
