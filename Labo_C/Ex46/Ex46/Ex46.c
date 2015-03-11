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
		
		if(ret > 0 && *to >= 0)
			ok = 1;
	}
}

int main(void) {
	int a, fibo;

	printf("Entrer un rang pour Fibonacci: ");
	scanfint(&a);

	if(a == 0) {
		fibo = 0;

	} else {
		if(a == 1) {
			fibo = 1;

		} else {
			
		}
	}

	/* for(i = 1; i <= a; i++)
		somme += 1/(float) i; */

	printf("Fibonnaci rang %d = %d\n", a, fibo);

	fflush(stdin);
	getchar();

	return 0;
}