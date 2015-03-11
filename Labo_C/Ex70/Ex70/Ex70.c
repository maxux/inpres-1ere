/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :	Vérifier si matrice diagonal				*/
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
	int matrice[MAX_SIZE][MAX_SIZE], i, j, dimens, inc, trace = 0;
	int *pmatrice;

	

	fflush(stdin);
	getchar();

	return 0;
}