/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :												*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void scanfint(int *to) {
	char ok = 0;
	int ret;

	while(!ok) {
		fflush(stdin);
		ret = scanf("%d", to);
		
		if(ret > 0)
			ok = 1;

		if(*to < 1)
			*to = -*to;
	}
}

int main(void) {
	int chiffre, i;
	double fact = 1;

	printf("Entrez un chiffre dont la factoriel sera calcule: ");
	scanfint(&chiffre);

	for(i = 2; i <= chiffre; i++)
		fact *= i;

	printf("Factoriel %d = %.1lf\n", chiffre, fact);

	fflush(stdin);
	getchar();

	return 0;
}