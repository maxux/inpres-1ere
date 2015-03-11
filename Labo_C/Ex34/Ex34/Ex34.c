/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Prix dégressant								*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int unitaire, qt;
	float total = 0;

	printf("Entrez le prix unitaire: ");
	fflush(stdin);
	scanf("%d", &unitaire);

	printf("Entrez la quantite: ");
	fflush(stdin);
	scanf("%d", &qt);

	printf("\n\n------------------------------------------\n");
	printf(" > %d articles: %d euro\n", qt, qt * unitaire);

	total = ((float) unitaire * qt);

	if(qt > 149) {
		printf(" > Reduction: 10%%\n");
		total *= (float) 0.90;			/* 10% Réduction */

	} else {
		if(qt > 99) {
			printf(" > Reduction: 5%%\n");
			total *= (float) 0.90;		/* 5% Réduction */

		} else {
			/* Frais de port */
			printf(" > Frais de port: 10 euro\n");
			total += 10;
		}
	}

	if(qt > 49) {
		printf(" > Vous avez un cadeau en plus\n");
	}

	printf("------------------------------------------\n");
	printf("                         Total: %.2f euro\n", total);

	fflush(stdin);
	getchar();

	return 0;
}