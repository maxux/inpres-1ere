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
	int unitaire, qt, tvaid;

	printf("Prix unitaire HTVA: ");
	fflush(stdin);
	scanf("%d", &unitaire);

	printf("Quantite: ");
	fflush(stdin);
	scanf("%d", &qt);

	printf("\n1: 6%%\n");
	printf("2: 19%%\n");
	printf("3: 21%%\n");
	printf("ID Tva: ");
	fflush(stdin);
	scanf("%d", &tvaid);

	switch(tvaid) {
		case 1:
			printf("\nTotal: %.3f\n", (qt*unitaire) * 1.06);
			break;

		case 2:
			printf("\nTotal: %.3f\n", (qt*unitaire) * 1.19);
			break;

		case 3:
			printf("\nTotal: %.3f\n", (qt*unitaire) * 1.21);
			break;

		default:
			printf("\nTVA Inconnue.\n");
	}

	fflush(stdin);
	getchar();

	return 0;
}