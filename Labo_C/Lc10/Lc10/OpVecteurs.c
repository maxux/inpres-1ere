#include "LC10-Daniel.h"
#include "Misc.h"
#include "OpVecteurs.h"

#include <stdio.h>

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

/* Encode les cases d'un vecteur						*/
/* @args: pointeur sur le vecteur && taille du vecteur	*/
int encode_vect(int *pvect, int vsize) {
	int i;

	for(i = 0; i < vsize; i++) {
		printf("Case [%d]: ", i + 1);

		scanfint(pvect, NO_RANGE);
		pvect++;
	}

	return CODE_SUCCESS;
}

/* Cherche une occurence via la méthode de la sentinelle		*/
/* @args: pointeur sur le vecteur && taille du vecteur && cible	*/
int find_vect(int *pvect, int vsize, int target) {
	int i = 0;

	*(pvect + vsize) = target;		/* Sentinelle: vect + 1 = cible			*/

	while(*pvect != target) {		/* Tant qu'on a pas trouvé, on continue	*/
		pvect++;
		i++;
	}

	if(i == vsize) {				/* Si on est a la case rajoutée, on a pas trouvé.	*/
		return ERR_NOT_FOUND;

	} else return i;				/* Sinon on retourne la position où on a trouvé		*/
}

/* Insert une valeur par "insertion dans un vecteur"				*/
/* @args:   pointeur sur le vecteur && taille du vecteur && cible	*/
/* @return: la nouvelle taille du vecteur							*/
int insert_vect(int *vect, int vsize, int target) {
	int i, *read, *write;

	read  = vect + vsize - 1;			/* On initialise le pointeur de lecture sur le dernier élement						*/
	write = read + 1;					/* On initialise le pointeur d'écriture sur le dernier élement + 1 (hors vecteur)	*/

	for(i = vsize + 1; i > 0 && target < *read; i--) {	/* Tant qu'on a pas trouvé			*/
		*write = *read;
		
		read--;				/* On passe à l'élement suivant	*/
		write--;
	}

	*write = target;

	return vsize + 1;		/* On retourne la nouvelle taille du tableau	*/
}

/* Trie un vecteur par la méthode d'insertion			*/
/* @args: pointeur sur un vecteur && taille du vecteur	*/
void order_vect(int *vect, int vsize) {
    int i, *value;

	value = vect + 1;		/* La première valeur a chercher est la case 2	*/

	for(i = 1; i < vsize; i++, value++)
        insert_vect(vect, i, *value);		/* Pour chaque case, on l'ajoute à la bonne place	*/		
}
