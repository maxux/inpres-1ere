/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Formatage d'une durée en minute				*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int min;

	printf("Saisissez une dure en minute: ");
	
	fflush(stdin);
	scanf("%d", &min);

	printf("\nDuree: %dh%d\n", (min / 60), (min % 60));

	fflush(stdin);
	getchar();

	return 0;
}