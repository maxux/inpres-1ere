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
		
		if(ret > 0 && *to > 0 && *to < 513)
			ok = 1;

		if(*to < 1)
			*to = -*to;
	}
}

int main(void) {
	/*

		FIX ME !

	*/
	int *vect, *pvect, cnt, moy, i, ecart;

	printf("Entrez un nombre de valeurs 0 < x < 512: ");
	scanfint(&cnt);

	vect = calloc(cnt, sizeof(int));
	pvect = vect;

	for(i = 0; i < cnt; i++, pvect++) {
		printf("Entrez la valeur %d: ", i + 1);
		scanfint(pvect);
	}

	pvect = vect;
	printf("----------\n");

	moy = 0;
	for(i = 0; i < cnt; i++, pvect++) {
		printf("Valeur %d => %d\n", i + 1, *pvect);
		moy += *pvect;
	}

	pvect = vect;
	printf("----------\n");

	moy /= cnt;
	printf("La moyenne est de: %d\n", moy);

	printf("----------\n");

	for(i = 0; i < cnt; i++, pvect++) {
		if(*pvect > moy)
			ecart = *pvect - moy;
		else
			ecart = moy - *pvect;

		printf("L'ecart de %d par rapport a la moyenne (%d) est de: %d\n", *pvect, moy, ecart);
	}

	fflush(stdin);
	getchar();

	return 0;
}