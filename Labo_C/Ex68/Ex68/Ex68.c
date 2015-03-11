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
/* #define ALLOC_DYN */

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

#ifdef ALLOC_DYN
	void printMatrice(int **matrice, int l, int c) {
		int *pmatrice, i, j;

		pmatrice = *matrice;

		for(i = 0; i < l; i++) {
			for(j = 0; j < c; j++) {
				printf("Valeur [%d][%d]: %d\n", i, j, *pmatrice);
				pmatrice++;
			}
		}
	}
#else
	void printMatrice(int matrice[][T_SIZE], int l, int c) {
		int *pmatrice, i, j;

		pmatrice = &matrice[0][0];

		for(i = 0; i < l; i++) {
			for(j = 0; j < c; j++) {
				printf("Valeur [%d][%d]: %d\n", i, j, *pmatrice);
				pmatrice++;
			}

			pmatrice += T_SIZE - c - 1;
		}
	}
#endif

int main(void) {
	#ifdef ALLOC_DYN
		int **matrice;
	#else
		int matrice[T_SIZE][T_SIZE];
	#endif

	int i, j, l, c, scalaire, dimens;
	int *pmatrice;


	/* Demande de la dimension */
	printf("Nombre de ligne: ");
	scanfint(&l);

	printf("Nombre de colone: ");
	scanfint(&c);

	dimens = l * c;

	#ifdef ALLOC_DYN
		/* Allocation dynamique */
		matrice = (int **) malloc(sizeof(int*) * l);

		for(i = 0; i < c; i++)
			matrice[i] = (int *) malloc(sizeof(int) * c);

		/* Assignations */
		pmatrice = *matrice;
	#else
		pmatrice = &matrice[0][0];
	#endif

	for(i = 0; i < l; i++) {
		for(j = 0; j < c; j++) {
			printf("Entrez la valeur [%d][%d]: ", i, j);
			scanfint(pmatrice);

			pmatrice++;
		}

		pmatrice += T_SIZE - c - 1;
	}

	/* Affichage */
	printMatrice(matrice, l, c);

	/* Traitement */
	/* Vérification: Multiplication par un scalaire */
	printf("Entrez un scalaire: ");
	scanfint(&scalaire);

	#ifdef ALLOC_DYN
		pmatrice = *matrice;
	#else
		pmatrice = &matrice[0][0];
	#endif

	#ifdef ALLOC_DYN
		for(i = 0; i < dimens; i++) {
			*pmatrice *= scalaire;
			pmatrice++;
		}
	#else	
		for(i = 0; i < l; i++) {
			for(j = 0; j < c; j++) {
				*pmatrice *= scalaire;
				pmatrice++;
			}

			pmatrice += T_SIZE - c - 1;
		}
	#endif

	/* Affichage du nouveau tableau */
	printMatrice(matrice, l, c);

	fflush(stdin);
	getchar();

	return 0;
}