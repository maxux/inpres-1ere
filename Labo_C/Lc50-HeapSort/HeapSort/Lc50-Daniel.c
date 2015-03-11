#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "HeapSort.h"

int main(void) {
	int *vect, nbe, i;
	/* int nbe, i, vect[] = {9, 5, 87, 54, 897, 5, 12, 51, 8, 432, 18, 45, 641, 54, 984, 251, 98};
	nbe = sizeof(vect) / sizeof(int); */

	printf("Nombre d'elements: ");
	nbe = readint();

	vect = (int *) malloc(sizeof(int) * nbe);
	if(vect == NULL)
		exit(1);

	for(i = 0; i < nbe; i++) {
		printf("Element %d: ", i+1);
		*(vect+i) = readint();
	}

	printf("-> ");
	for(i = 0; i < nbe; i++)
		printf("%d, ", *(vect+i));

	printf("\nSorting...\n");
	heapsort(vect, nbe);

	printf("-> ");
	for(i = 0; i < nbe; i++)
		printf("%d, ", *(vect+i));

	getchar();
	return 0;
}

/* Permet de lire un int sur l'entrée standart */
/* Return: un entier                           */
int readint() {
	char buffer[16];
	int temp = 0;

	while(temp <= 0) {
		fgets(buffer, sizeof(buffer), stdin);
		temp = atoi(buffer);
	}

	return temp;
}

/* Permet de trier un vecteur de int, par la méthode du tri par tas      */
/* @args: pointeur vers la première case du vecteur, le nombre d'élement */
void heapsort(int *vect, int nbe) {
	int i;

	for(i = nbe / 2; i >= 0; i--)
		paterner(vect, i, nbe - 1);

	for(i = nbe - 1; i >= 1; i--) {
		alternate(vect, vect+i);
		paterner(vect, 0, i - 1);
	}
}

/* Paterne un element avec son/ses fils dans un vecteur.								*/
/* @args: pointeur vers le début du vecteur, l'élement, le nombre d'élement du vecteur  */
void paterner(int *vect, int element, int nbe) {
	int ok = 0, child, use;

	use = element * 2;	/* Pré-calcul (l'élement * 2) pour ne pas le calculer plus loin */

	while((use <= nbe) && ok != 1) {
		if(use == nbe || (vect[element * 2] > vect[element * 2 + 1]))
			child = use;
		else
			child = use + 1;

		if(*(vect+element) < *(vect+child)) {		/* Si l'élement est plus petit  */
			alternate(vect+element, vect+child);	/* On inverse					*/
			element = child;						/* On stocke la nouvelle valeur */

		} else ok = 1;

		use = element * 2;
	} 
}

/* Permet d'inverser le contenu (int) de deux variables                   */
/* @args: adresse de la première variable, adresse de la seconde variable */
void alternate(int *str1, int *str2) {
	int str3;

	str3 = *str1;
	*str1 = *str2;
	*str2 = str3;
}