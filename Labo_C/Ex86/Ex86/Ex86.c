/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :					*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define NAME_SIZE	32

void scanfword(char *to) {
	char ok = 0;
	int ret;

	while(!ok) {
		fflush(stdin);
		printf("# ");

		ret = scanf("%s", to);
		
		if(ret > 0 && *to > 0)
			ok = 1;
	}
}

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

void DisplayTable(char *tableau, int lines, short nsize) {
	short i;

	for(i = 0; i < lines; i++) {
		printf("[%d]: %s\n", i + 1, tableau);
		tableau += nsize;
	}
}

void OrderInsertionTable(char *tableau, char insert[], short last, short nsize) {
	char *read, *write;

	read  = tableau + (last * nsize);
	write = read + nsize;

	/* Tant que l'insertion est plus bas que la case en cours, on décale */
	while(last > -1 && strcmp(insert, read) < 0) {
		strcpy(write, read);

		write -= nsize;
		read  -= nsize;

		last--;
	}

	/* Insertion de l'élément */
	strcpy(write, insert);
}

void OrderTable(char *tableau, int lines, short nsize) {
	short i;
	char temp[NAME_SIZE];
	/* Un malloc serait mieux qu'un [NAME_SIZE] dans une fonction. */

	for(i = 1; i < lines; i++) {
		/* On copie la chaine qu'on veut traiter */
		strcpy(temp, (tableau + (i * nsize)));

		/* On trie par insertion */
		OrderInsertionTable(tableau, temp, i - 1, nsize);
	}
}


int main(void) {
	char tableau[256][NAME_SIZE];
	int lines;
	short i;

	printf("Nombre d'entrees: ");
	scanfint(&lines);

	for(i = 0; i < lines; i++) {
		printf("Nom %d: ", i + 1);
		scanfword(&tableau[i][0]);
	}

	/* Affiche le tableau */
	DisplayTable(&tableau[0][0], lines, NAME_SIZE);

	/* Trie le tableau */
	OrderTable(&tableau[0][0], lines, NAME_SIZE);

	/* Affiche le tableau trié */
	printf("---------------\n");
	DisplayTable(&tableau[0][0], lines, NAME_SIZE);

	fflush(stdin);
	getchar();

	return 0;
}