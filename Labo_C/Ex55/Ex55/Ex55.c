/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :												*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

int main(void) {
	int a, b, som;

	for(a = 0; a <= 99; a += 11) {
		for(b = 0; b <= 99; b += 11) {
			som = (a * 100) + b;

			if(sqrt(som) / ((int) sqrt(som)) == 1)
				printf("AABB: %d est carre parfait.\n", som);
		}
	}

	fflush(stdin);
	getchar();

	return 0;
}