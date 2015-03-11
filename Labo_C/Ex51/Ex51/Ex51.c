/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :	Calcul d'une somme sans dépasser une lim	*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void scanfint(int *to) {
	char ok = 0;
	int ret;

	while(!ok) {
		fflush(stdin);
		printf("# ");

		ret = scanf("%d", to);
		
		if(ret > 0)
			ok = 1;

		if(*to < 1)
			*to = -*to;
	}
}

int main(void) {
	int a, b = -1, somme, c;

	printf("Entrez un chiffre de base: ");
	scanfint(&a);

	do {
		printf("Entrez un chiffre de limite: ");
		scanfint(&b);

	} while(b < a);

	somme = a;
	while(somme < b)
		somme += ++a;

	somme -= a;

	printf("Somme = %d\n", somme);

	fflush(stdin);
	getchar();

	return 0;
}