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
		printf("# ");

		ret = scanf("%d", to);
		
		if(ret > 0 && *to > 0)
			ok = 1;
	}
}

int main(void) {
	int a, i, somme = 0;

	printf("Entrer un entier positif: ");
	scanfint(&a);

	for(i = 1; i <= a; i++)
		somme += i;

	printf("La somme est de: %d\n", somme);

	fflush(stdin);
	getchar();

	return 0;
}