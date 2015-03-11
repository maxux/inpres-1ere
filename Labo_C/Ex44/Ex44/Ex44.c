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
	int count, i, somme, temp;

	printf("Entrez un nombre de valeur a entrer: ");
	fflush(stdin);
	scanfint(&count);

	if(count != 0) {
		somme = 0;
		for(i = 0; i < count; i++) {
			printf("Valeur %d: ", i + 1);
			scanfint(&temp);
			somme += temp;
		}

	} else {
		somme = 0;
		count = 1;
	}

	printf("\nMoyenne: %.3f\n", somme / (float) count);
	
	fflush(stdin);
	getchar();
	
	return 0;
}