/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :												*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define VCOUNT	10

int main(void) {
	int vect[VCOUNT] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	int i, j, temp;

	i = 0;
	j = VCOUNT - 1;

	for(; i < VCOUNT / 2; i++, j--) {
		temp = vect[i];
		vect[i] = vect[j];
		vect[j] = temp;
	}

	for(i = 0; i < VCOUNT; i++)
		printf("%d\n", vect[i]);

	fflush(stdin);
	getchar();

	return 0;
}