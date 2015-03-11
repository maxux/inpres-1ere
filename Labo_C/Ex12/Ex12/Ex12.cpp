/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Calcul d'une consommation au 100			*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int compt1, compt2, plein;

	printf("Entrez le nombre de km au premier plein: ");

	fflush(stdin);
	scanf("%d", &compt1);

	printf("Entrez le nombre de km au deuxieme plein: ");

	fflush(stdin);
	scanf("%d", &compt2);

	printf("Entrez la quantite de carburant que vous avez remis: ");

	fflush(stdin);
	scanf("%d", &plein);

	printf("Vous consommez %.3f L/100\n", ((plein / ((float) compt2 - compt1)) * 100));

	fflush(stdin);
	getchar();

	return 0;
}