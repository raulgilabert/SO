#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int is_space(char c) {
    return (c == ' ' || c == '.' || c == ',' || c == '\n');
}

int count_words(char str[]) {
    int words = 0;
    int i = 0;
    int last = 0;
    for (i = 0; str[i] != '\0'; ++i) {
	if (is_space(str[i]) && i > 0 && !is_space(str[i - 1])) {
	    ++words;
	}
    }

    if (i > 0 && !is_space(str[i - 1]))
	++words;

    return words;
}

int main(int argc, char *argv[]) {
    char buffer[16];
    sprintf(buffer, "%d palabras\n", count_words(argv[1]));
    write(1, buffer, strlen(buffer));
}
