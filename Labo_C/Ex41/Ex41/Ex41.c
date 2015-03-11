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
	int table, i;

	printf("Entrez un nombre dont la table -> 10 sera calcule: ");
	fflush(stdin);
	scanfint(&table);

	printf("\n");
	for(i = 1; i < 11; i++)
		printf("%3.d * %3.d = %4.d\n", i, table, i * table);

	fflush(stdin);
	getchar();

	return 0;
}