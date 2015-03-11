#include "Display.h"
#include <stdio.h>

/* Affiche (de manière formaté) un tableau de date										*/
/* @args: pointeur vers un tableau date (3 colonne) && taille du tableau (nb lignes)	*/
void display_date(short *date, short tsize) {
	short i;

	printf(" Day | Mon | Year\n"\
		   "-----+-----+-----\n");

	for(i = 0; i < tsize; i++, date += 3) {
		printf(" %3hd | %3hd | %hd\n", *date, *(date + 1), *(date + 2));
	}
}