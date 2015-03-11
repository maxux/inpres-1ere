/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Calcul de périmètre et aire d'un cercle		*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define PI	3.14159265

float aire_disque(float rayon) {
	return (float) PI * (rayon * rayon);
}

float perim_disque(float rayon) {
	return (float) PI * rayon;
}

int main(void) {
	float r, perim, aire;

	printf("Rayon: ");

	fflush(stdin);
	scanf("%f", &r);

	aire  = aire_disque(r);
	perim = perim_disque(r);

	printf("\nL'air du cercle est de: %.2f\n", aire);
	printf("Le perimetre du cercle est de: %.2f\n", perim);
	
	/* End Of Code */
	fflush(stdin);
	getchar();

	return 0;
}