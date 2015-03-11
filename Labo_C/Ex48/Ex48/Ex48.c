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
		
		if(ret > 0)
			ok = 1;

		if(*to < 1)
			*to = -*to;
	}
}

int main(void) {
	int i, base, expo;
	double result;

	printf("Entrez une base: ");
	fflush(stdin);
	scanfint(&base);

	printf("Entrez une puissance: ");
	fflush(stdin);
	scanfint(&expo);

	if(expo != 0) {
		result = base;
		for(i = 2; i <= expo; i++) {
			result *= base;
		}

	} else result = 1;

	printf("\n%d puissance %d = %.0lf\n", base, expo, result);
	
	fflush(stdin);
	getchar();
	
	return 0;
}