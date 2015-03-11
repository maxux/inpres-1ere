/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :	Fibonacci rang n							*/
/********************************************************/

/* 
	Fib(0) = 0
	Fib(1) = 1
	Fib(n) = Fib(n-1) + Fib(n-2)
*/

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

int fibonacci(int rang) {
	int i;
	int temp[3] = {0, 1, 0};

	if(rang == 0) {
		return 0;

	} else {
		if(rang == 1) {
			return 1;

		} else {
			for(i = 2; i <= rang; i++) {
				temp[2] = temp[0] + temp[1];
				temp[0] = temp[1];
				temp[1] = temp[2];
			}
			
			return temp[2];
		}
	}
}

int main(void) {
	int n, i;
	double fibo = 0;

	printf("Entrez un rang n: ");
	scanfint(&n);

	if(n == 0) {
		printf("Fib(0) = 0\n");

	} else {
		if (n == 1) {
			printf("Fib(1) = 1\n");

		} else {
			fibo = fibonacci(n);
			printf("Fib(%d) = %.0lf\n", n, fibo);
		}
	}
	
	fflush(stdin);
	getchar();
	
	return 0;
}