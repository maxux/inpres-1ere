/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :	Multiplication d'une matrice par scalaire	*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define T_SIZE		128

void scanfint(int *to) {
	char ok = 0;
	int ret;

	while(!ok) {
		fflush(stdin);
		printf("# ");

		ret = scanf("%d", to);
		
		if(ret > 0 && *to > 0 && *to < T_SIZE)
			ok = 1;

		if(*to < 1)
			*to = -*to;
	}
}

void printMatrice(int matrice[][T_SIZE], int l, int c) {
	int *pmatrice, i, j;

	pmatrice = &matrice[0][0];

	for(i = 0; i < l; i++) {
		for(j = 0; j < c; j++) {
			printf("valeur [%d][%d]: %d\n", i, j, *pmatrice);
			pmatrice++;
		}

		pmatrice += T_SIZE - c - 1;
	}
}

void getDimension(int *l, int *c) {
	/* Demande de la dimension */
	printf("Nombre de ligne: ");
	scanfint(l);

	printf("Nombre de colone: ");
	scanfint(c);
}

int main(void) {
	int matrice1[T_SIZE][T_SIZE];
	int matrice2[T_SIZE][T_SIZE];
	int i, j, l1, c1, l2, c2;

	int *pmatrice1, *pmatrice2, fail = 0;

	getDimension(&l1, &c1);
	getDimension(&l2, &c2);

	

	if(l1 == l2 && l2 == c2) {
		pmatrice = &matrice[0][0];

		for(i = 0; i < l1; i++) {
			for(j = 0; j < c1; j++) {
				printf("Entrez la valeur [%d][%d]: ", i, j);
				scanfint(pmatrice);

				pmatrice++;
			}

			pmatrice += T_SIZE - c1 - 1;
		}

		/* Affichage */
		printMatrice(matrice, l1, c1);

		/* Traitement */
		/* Vérification: Matrice identique ? */
		pmatrice = &matrice[0][0];

		for(i = 0; i < l1; i++) {
			for(j = 0; j < c1; j++) {
				if(
				pmatrice++;
			}
			
			pmatrice += T_SIZE - c1 - 1;
		}

		/* Affichage du nouveau tableau */
		printMatrice(matrice, l1, c1);

	}

	if(fail)
		printf("La matrice n'est pas egale\n");

	else printf("La matrice est identique\n");

	fflush(stdin);
	getchar();

	return 0;
}