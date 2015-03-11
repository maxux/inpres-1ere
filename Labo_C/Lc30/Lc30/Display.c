#include <stdio.h>
#include "Display.h"

/* Affiche le contenu d'un tableau, via son vecteur de pointeur.
   @args: pointeur vers le début du vecteur de pointeur
*/
void DisplayByIndex(char **index) {
	short i = 0;

	while(*index != NULL) {
		printf("[%d][%p] %s\n", i + 1, *index, *index);

		*(index)++;
		i++;
	}
}

/* Affiche le contenu d'un tableau à deux dimensions
   @args: pointeur vers le début du tableau, le nombre de ligne, la longueur de chaque ligne
*/
void DisplayTable(char *table, short lines, short length) {
	short i;

	for(i = 0; i < lines; i++)
		printf("[%d] %s\n", i + 1, table + (i * length));
}