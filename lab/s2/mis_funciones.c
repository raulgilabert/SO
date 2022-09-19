#include "mis_funciones.h"

unsigned int char2int(char c) {
    return (int) c - '0';
}

int mi_atoi(char *s) {
    int num = 0;

    // En caso de que sea negativo se guarda que lo es y se adelanta una
    // posición en memoria el puntero
int neg = 0;
    if (s[0] == '-') {
	neg = 1;
++s;
    }

    // Se convierte el string a número
    for (int i = 0; s[i] != '\0'; ++i) {
	num *= 10;
	num += char2int(s[i]);
    }

    if (neg == 1)
	num = 0 - num;

    return num;
}

int esNumero (char *str) {
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


