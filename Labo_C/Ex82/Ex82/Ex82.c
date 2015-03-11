/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :							*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void scanfint(int *to, int min, int max) {
	char ok = 0;
	int ret;

	while(!ok) {
		fflush(stdin);
		printf("# ");

		ret = scanf("%d", to);
		
		if(min > max) {
			if(ret > 0)
				ok = 1;

		} else {
			if(ret > 0 && *to > min && *to <= max)
				ok = 1;
		}
	}
}

void permuter(int *a, int *b) {
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(void) {
	int a, b;

	printf("Entrez une valeur: ");
	scanfint(&a, 2, 1);

	printf("Entrez une valeur: ");
	scanfint(&b, 2, 1);

	permuter(&a, &b);
	printf("Les variables ont ete permutes: a = %d | b = %d\n", a, b);

	fflush(stdin);
	getchar();

	return 0;
}