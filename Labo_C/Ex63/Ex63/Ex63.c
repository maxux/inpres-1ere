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

int tasser(int *tbl, int nb) {
	int i, tmp, *pvect, *pvect2, nnb;

	nnb = nb;
	tmp = *tbl;
	pvect = tbl + 1;
	pvect2 = tbl + 1;

	for(i = 1; i < nb; i++, pvect2++) {
		if(*pvect2 != tmp) {
			*pvect = *pvect2;
			tmp = *pvect;
			pvect++;

		} else nnb--;
	}

	return nnb;
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

	nb = tasser(vect, nb);
	pvect = vect;

	for(i = 0; i < nb; i++, pvect++) {
		printf("%d ", *pvect);
	}

	fflush(stdin);
	getchar();

	return 0;
}