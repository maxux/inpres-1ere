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
	int a, rep = 0;

	printf("Entrez un entier positif ");
	scanfint(&a);

	while(rep * rep <= a)
		rep++;

	rep--;

	printf("La partie entiere de la racine carre = %d\n", rep);

	fflush(stdin);
	getchar();

	return 0;
}