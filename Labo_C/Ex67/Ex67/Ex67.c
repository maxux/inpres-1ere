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

#define MAX_SIZE	50

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
	int matrice[MAX_SIZE][MAX_SIZE], i, j, dimens, inc, trace = 0;
	int *pmatrice;

	printf("Entrez le nombre de ligne: ");
	scanfint(&dimens);

	pmatrice = &matrice[0][0];

	for(i = 0; i < dimens; i++) {
		for(j = 0; j < dimens; j++, pmatrice++) {
			printf("Entrez la valeur de la ligne %d, colonne %d : ", i + 1, j + 1);
			scanfint(pmatrice);
		}

		pmatrice += (MAX_SIZE - j);
	}

	pmatrice = &matrice[0][0];

	printf("\n");

	inc = 2;

	for(i = 1; i <= dimens; i++, pmatrice += 1 + MAX_SIZE) {
		printf("%*.2d\n", inc, *pmatrice);
		trace += *pmatrice;
		inc += 2;
	}

	printf("\nTrace: %d\n", trace);

	fflush(stdin);
	getchar();

	return 0;
}