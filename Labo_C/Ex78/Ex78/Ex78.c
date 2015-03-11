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

void getMatriceData(int *matrice, int lines) {
	int i, j, *pmatrice;

	pmatrice = matrice;

	for(i = 0; i < lines; i++) {
		for(j = 0; j < lines; j++, pmatrice++) {
			printf("Element [%d][%d]: ", i + 1, j + 1);
			scanfint(pmatrice);
		}
	}
}

void showMatriceData(int *matrice, int lines) {
	int i, j, *pmatrice;

	pmatrice = matrice;

	for(i = 0; i < lines; i++) {
		for(j = 0; j < lines; j++, pmatrice++)
			printf("%3.d ", *pmatrice);

		printf("\n");
	}
}

void permuter(int *a, int *b) {
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/* void transposeMatrice(int *matrice, int lines) {
	int i, j, *pmatl, *pmatr;

	for(i = 0; i < lines; i++) {
		pmatl = matrice + (i * lines) + i + 1;
		pmatr = matrice + (i * lines) + lines + i;

		for(j = i; j < lines - 1; j++) {
			permuter(pmatl, pmatr);
		
			pmatl++;
			pmatr += lines;
		}
	}
} */

void transposeMatrice(int *matrice, int lines) {
	int i, j, *pmatl, *pmatr;

	for(i = 0; i < lines; i++) {
		pmatl = matrice + (i * lines) + i + 1;
		pmatr = matrice + (i * lines) + lines + i;

		for(j = i; j < lines - 1; j++) {
			permuter(pmatl, pmatr);
		
			pmatl++;
			pmatr += lines;
		}
	}
}

int main(void) {
	int *matrice, *pmatrice;
	int lines;

	printf("Entrez le nombre de ligne: ");
	scanfint(&lines);

	/* Allocation de la matrice */
	matrice = (int*) malloc(sizeof(int) * lines * lines);
	pmatrice = matrice;

	/* Récupération des valeurs */
	getMatriceData(matrice, lines);

	/* Affichage des valeurs */
	printf("_________________________\n");
	showMatriceData(matrice, lines);

	/* Transposer */
	transposeMatrice(matrice, lines);

	/* Affichage des nouvelles valeurs */
	printf("_________________________\n");
	showMatriceData(matrice, lines);

	fflush(stdin);
	getchar();

	return 0;
}