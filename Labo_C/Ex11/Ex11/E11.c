/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Calcul du poids idéale						*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void getTaille(int *taille) {
	printf("Entrez votre taille [cm]: ");

	fflush(stdin);
	scanf("%d", taille);
}

void printPoidsIdeal(float poids) {
	if(poids > 1) {
		printf("Votre poids ideale est de: %f\n", poids);

	} else {
		printf("Votre taille est invalide.\n");
	}
}

int main(void) {
	float poids;
	int taille;
	char gender[1];

	printf("Entrez votre sexe [H/F]: ");

	fflush(stdin);
	gender[0] = getchar();

	if(gender[0] == 'h' || gender[0] == 'H') {
		/* Traitement pour une homme */
		getTaille(&taille);
		poids = (taille - 100) - ((float) (taille - 150) / 4);
		printPoidsIdeal(poids);

	} else if(gender[0] == 'f' || gender[0] == 'F') {
		/* Traitement pour une femme */
		getTaille(&taille);
		poids = (taille - 100) - ((float) (taille - 150) / 2);
		printPoidsIdeal(poids);

	} else {
		/* Traitement pour un trans ou un truc du genre... aucune idée */
		printf("Votre genre m'est inconnu :/\n");
	}

	fflush(stdin);
	getchar();

	return 0;
}