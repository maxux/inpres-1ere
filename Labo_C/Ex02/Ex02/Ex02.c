/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Calcul d'un taux d'intéret					*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int capital;
	float gain, total, interet;

	/* Nombres de base */
	printf("Capital de depart: ");

	fflush(stdin);
	scanf("%d", &capital);

	printf("Taux d'interet / an %%: ");

	fflush(stdin);
	scanf("%f", &interet);

	/* Calcul */
	total  = (float)(capital * (1 + (interet / 100)));
	gain = (float)(total - capital);

	printf("\nVous aurez gagne: %.2f\n", gain);
	printf("Votre gain apres un an sera de: %.3f\n", total);
	
	/* End Of Code */
	fflush(stdin);
	getchar();

	return 0;
}