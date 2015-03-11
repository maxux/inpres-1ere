/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :												*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAY	25
#define MAX_RAN		5000

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

int rrand(int max) {
	return 1 + (int) (max * (rand() / (RAND_MAX + 1.0)));
}

int main(void) {
	int a, i, ran, found;

	/* Better Random */
	srand((int) time(NULL));
	a = rrand(10);

	for(i = 0; i < a; i++)
		rand();

	/* End Of Init Random */
	ran = rrand(MAX_RAN);

	printf("Entrez un chiffre entre 0 et %d\n", MAX_RAN);

	found = 0;
	for(i = 0; i < MAX_PLAY; i++) {
		scanfint(&a);

		if(a > ran) {
			printf("Nous cherchons un chiffre plus petit que %d\n", a);

		} else {
			if(a < ran) {
				printf("Nous cherchons un chiffre plus grand que %d\n", a);

			} else {
				printf("Bravo ! Vous avez trouve en %d tours\n", i);
				i = MAX_PLAY;
				found = 1;
			}
		}
	}

	if(!found)
		printf("\nDesole, vous n'avez pas trouve. Nous cherchions: %d\n", ran);

	fflush(stdin);
	getchar();

	return 0;
}