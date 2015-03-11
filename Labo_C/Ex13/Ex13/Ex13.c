/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Convertisseur °C -> °F						*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define NBR_BILLETS		7
#define NBR_PIECES		2

int main(void) {
	int somme, i, temp;
	int billets[7] = {500, 200, 100, 50, 20, 10, 5};
	int pieces[2]  = {2, 1};

	printf("Entrez une somme entiere en euro: ");

	fflush(stdin);
	scanf("%d", &somme);

	for(i = 0; i < NBR_BILLETS; i++) {
		temp = (somme % billets[i]);

		printf("Billets: %d: %d\n", billets[i], ((somme - temp) / billets[i]));
		somme = temp;
	}

	for(i = 0; i < NBR_PIECES; i++) {
		temp = (somme % pieces[i]);

		printf("Billets: %d: %d\n", pieces[i], ((somme - temp) / pieces[i]));
		somme = temp;
	}

	fflush(stdin);
	getchar();

	return 0;
}