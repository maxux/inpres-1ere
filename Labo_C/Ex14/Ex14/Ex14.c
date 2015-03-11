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
		
		if(ret > 0 && *to > 0)
			ok = 1;
	}
}

int main(void) {
	int value, i, j;
	char unit[] = {'U', 'D', 'C', 'M'};

	printf("Entrez un chiffre positif: ");
	scanfint(&value);

	i = 10;
	j = 0;

	while(value / i > 0) {
		printf("%c: %d\n", unit[j], value % i);
		value /= i;

		j++;
		i *= 10;
	}

	fflush(stdin);
	getchar();
}