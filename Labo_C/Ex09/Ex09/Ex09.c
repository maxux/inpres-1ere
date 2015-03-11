/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Calcul d'une resistance equivalente (serie)	*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int res1, res2, equiv;

	printf("Entrez la resistance de la resistance 1: ");

	fflush(stdin);
	scanf("%d", &res1);

	printf("Entrez la resistance de la resistance 2: ");

	fflush(stdin);
	scanf("%d", &res2);

	/* Calcul */
	equiv = res1 + res2;

	printf("\nResistance equivalente (parallele): %d ohm\n", equiv);

	fflush(stdin);
	getchar();

	return 0;
}