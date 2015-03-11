/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Calcul de moyenne avec pondération			*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int a, b, x, y;
	float moy_pon;

	/* Nombres de base */
	printf("Veuillez saisir un entier: ");

	fflush(stdin);
	scanf("%d", &a);

	printf("Veuillez en saisir un deuxieme: ");

	fflush(stdin);
	scanf("%d", &b);

	/* Pondération */
	printf("Veuillez saisir la premiere ponderation: ");

	fflush(stdin);
	scanf("%d", &x);

	printf("Veuillez saisir la seconde ponderation: ");

	fflush(stdin);
	scanf("%d", &y);

	/* Calcul */
	moy_pon = (float)((x*a) + (y*b)) / (x+y);

	printf("\nLa moyenne ponderee est: %.2f\n", moy_pon);
	
	/* End Of Code */
	fflush(stdin);
	getchar();

	return 0;
}