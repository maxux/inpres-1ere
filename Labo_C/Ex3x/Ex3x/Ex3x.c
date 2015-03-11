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
	int cote;

	printf("Entrez une cote (0-100): ");
	fflush(stdin);
	scanf("%d", &cote);

	switch(cote / 10) {
		case 10:
		case 9:
			printf("Excellent\n");
			break;

		case 8:
			printf("Tres bien\n");
			break;

		case 7:
			printf("Bien\n");
			break;

		case 6:
			printf("Moyen\n");
			break;

		case 5:
			printf("Je sais plus\n");
			break;

		default:
			printf("Insuffisant\n");
	}

	fflush(stdin);
	getchar();

	return 0;
}