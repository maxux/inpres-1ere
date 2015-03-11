#include <stdio.h>
#include <stdlib.h>
#include "Lc70.h"

/* Encode un entier dans la dernière case d'un vecteur */
/* @args: pointeur vers la première case du vecteur, pointeur vers le nombre d'element dans le vecteur */
/* Return: 0 */
int Encodage(int *vect, int *nbelem) {
	char temp[6] = {'\n'};

	do {
		printf("\n * Ajouter: ");

		fflush(stdin);
		fgets(temp, sizeof(temp), stdin);

	} while(temp[0] == '\n' || (*(vect+*nbelem) = atoi(temp)) == 0);

	(*nbelem)++;
	return 0;
}

/* Affiche le contenu d'un vecteur */
/* @args: pointeur vers la premiere case du vecteur, pointeur vers le nombre d'element du vecteur */
/* Return: 0 */
int Affichage(int *vect, int *nbelem) {
	int i;

	printf(" * Vecteur: ");

	for(i = *nbelem; i > 0; i--)
		printf("%d, ", *(vect++));

	printf("\n");
	return 0;
}

/* Insert un élement dans un vecteur, à la bonne place */
/* @args: pointeur vers la première case du vecteur, la valeur à insérer, le nombre d'élement du vecteur */
/* Return: 0 */
void Insert(int *vect, int insert, int nbelem) {
	int *read, *write;

	read  = vect + nbelem;  /* Pointeur de lecture */
	write = read + 1;       /* Pointeur d'écriture */

	while(nbelem > -1 && *read > insert) {
		*write = *read;

		read--;
		write--;
		nbelem--;
	}

	*write = insert;    /* Ecrit l'adresse de l'élément à insérer à la bonne place */
}

/* Trie un vecteur par insertion simple */
/* @args: pointeur vers la premiere case du vecteur, pointeur vers le nombre d'element du vecteur */
/* Return: 0 */
int TriInsert(int *vect, int *nbelem) {
	int i = 1;
	int *first = vect;

	printf(" * Tri en cours...\n");

	while(i < *nbelem) {
		Insert(first, *(first+i), i - 1);
		i++;
	}

	return 0;
}

/* Calcul la somme d'un vecteur */
/* @args: pointeur vers la premiere case du vecteur, pointeur vers le nombre d'element du vecteur */
/* Return: la somme */
int Somme(int *vect, int *nbelem) {
	int somme = 0, i;

	for(i = 0; i < *nbelem; i++, vect++)
		somme += *vect;


	return somme;
}

/* Lance la boucle sur l'execution des fonctions */
/* @args: pointeur vers la premiere case du vecteur, le nombre d'element max, vecteur de pointeurs de fonctions */
void RunLoop(int *vect, int nbelem, fctpt *ptf) {
	int i, nbcur = 0;
	fctpt *doit;

	for(i = 0; i < nbelem; i++)
		for(doit = ptf; *doit != NULL; doit++)
			printf(" * Retour (0x%x): %d\n", doit, (*doit)(vect, &nbcur));
}

int main(int argc, char *argv[]) {
	int vect[100], nbelem;
	fctpt ptf[] = {Encodage, Affichage, TriInsert, Affichage, Somme, NULL};

	if(argc > 1) {
		nbelem = atoi(argv[1]);
		if(nbelem > 0 && nbelem < 100) {
			RunLoop(vect, nbelem, ptf);
			printf("Boucle termine.\n");

		} else printf("Invalid argument\n");
	} else printf("Missing arguments.\n");

	fflush(stdin);
	getchar();

	return 0;
}