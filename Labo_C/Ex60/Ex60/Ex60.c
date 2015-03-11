/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :												*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void scanfint(int *to) {
	char ok = 0;
	int ret;

	while(!ok) {
		fflush(stdin);
		printf("# ");

		ret = scanf("%d", to);
		
		if(ret > 0 && *to > 0)
			ok = 1;
	}
}

int croissant(int *tbl, int nb) {
	int i, tmp, *pvect;

	tmp = *tbl;
	pvect = tbl + 1;

	for(i = 1; i < nb; i++, pvect++) {
		if(*pvect <= tmp)
			return 0;
		
		tmp = *pvect;
	}

	return 1;
}

int decroissant(int *tbl, int nb) {
	int i, tmp, *pvect;

	tmp = *tbl;
	pvect = tbl + 1;

	for(i = 1; i < nb; i++, pvect++) {
		if(*pvect >= tmp)
			return 0;
		
		tmp = *pvect;
	}

	return 1;
}

int egaux(int *tbl, int nb) {
	int i, tmp, *pvect;

	tmp = *tbl;
	pvect = tbl + 1;

	for(i = 1; i < nb; i++, pvect++) {
		if(*pvect != tmp)
			return 0;
		
		tmp = *pvect;
	}

	return 1;
}

int main(void) {
	int *vect, *pvect, nb, i;

	printf("Entrez un nombre d'elements ");
	scanfint(&nb);

	vect = calloc(nb, sizeof(int));
	pvect = vect;

	for(i = 0; i < nb; i++, pvect++) {
		printf("Element %d: ", i + 1);
		scanfint(pvect);
	}
	
	pvect = vect;
	printf("\n");

	for(i = 0; i < nb; i++, pvect++) {
		printf("Element %d = %d\n", i + 1, *pvect);
	}

	printf("\n");

	if(croissant(vect, nb))
		printf("Vecteur croissant\n");

	else
		if(decroissant(vect, nb))
			printf("Vecteur decroissant\n");

		else
			if(egaux(vect, nb))
				printf("Vecteur egaux\n");

			else printf("Quedalle...\n");

	fflush(stdin);
	getchar();

	return 0;
}