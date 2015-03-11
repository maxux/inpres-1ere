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

void scanfint(int *to) {
	char ok = 0;
	int ret;

	while(!ok) {
		fflush(stdin);
		printf("# ");

		ret = scanf("%d", to);
		
		if(ret > 0 && *to > 0 && *to < 513)
			ok = 1;

		if(*to < 1)
			*to = -*to;
	}
}

int main(void) {
	/*
	int *vect, line, row, total, temp, i, j, ocl, occ;
	int *pvect;
	*/

	int vect[50][50], line, row, temp, i, j, ocl, occ;
	int *pvect;

	printf("Nombre de ligne: ");
	scanfint(&line);

	printf("Nombre de colonne: ");
	scanfint(&row);

	/*
	total = line * row;

	vect = malloc(sizeof(int) * total);

	pvect = vect;
	for(i = 0; i < line; i++, pvect++) {
		for(j = 0; j < row; j++, pvect++) {
			printf("Entrez la valeur de la ligne %d, colonne %d : ", i + 1, j + 1);
			scanfint(pvect);
		}
	}

	pvect = vect + 1;

	temp = *vect;
	j = 1, occ = 0, ocl = 0;

	for(i = 0; i < line; i++, pvect++) {
		for(; j < row; j++, pvect++) {
			if(*pvect > temp) {
				temp = *pvect;
				ocl = i;
				occ = j;
			}
		}

		j = 0;
	}

	*/

	pvect = &vect[0][0];

	for(i = 0; i < line; i++) {
		for(j = 0; j < row; j++, pvect++) {
			printf("Entrez la valeur de la ligne %d, colonne %d : ", i + 1, j + 1);
			scanfint(pvect);
		}

		pvect += (50 - j);
	}

	for (i=0;i<line;i++)
	{
		for (j=0;j<row;j++)
		{
			printf("%d ",vect[i][j]);
		}
		printf("\n");
	}
	pvect = &vect[0][1];
	temp = vect[0][0];
	j = 1, ocl = 0, occ = 0;



	for(i = 0; i < line; i++, pvect++) {
		for(; j < row; j++, pvect++) {
			if(*pvect > temp) {
				temp = *pvect;
				ocl = i;
				occ = j;
			}
		}

		pvect += (50 - j);
		j = 0;
	}

	/* Print Result */
	printf("Le maximum est [%d] a la ligne %d, colonne %d\n", temp, ocl + 1, occ + 1);

	fflush(stdin);
	getchar();

	return 0;
}