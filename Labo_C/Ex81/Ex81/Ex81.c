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

int main(void) {
	int data;

	printf("Entrez une valeur entre 5 et 30: ");
	scanfint(&data, 5, 30);
	printf("Vous avez entre: %d\n", data);

	printf("Entrez une valeur entre -50 et 50: ");
	scanfint(&data, -50, 50);
	printf("Vous avez entre: %d\n", data);

	printf("Entrez une valeur: ");
	scanfint(&data, 2, 1);
	printf("Vous avez entre: %d\n", data);

	fflush(stdin);
	getchar();

	return 0;
}