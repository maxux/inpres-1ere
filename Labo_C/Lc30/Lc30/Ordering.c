/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include "Lc30-Daniel.h"
#include "Ordering.h"
#include "Display.h"

/* Insertion d'un élement dans un vecteur de pointeur
   @args: vecteur de pointeur, chaine à insérer, adresse de l'élément à insérer, le numero dernière case
*/
void OrderInsertion(char **index, char *insert, short last) {
	char **read, **write;

	read  = index + last;   /* Pointeur de lecture */
	write = read + 1;       /* Pointeur d'écriture */

	/* Tant que l'insertion est plus bas que la case en cours, on décale */
	while(last > -1 && strcmp(*read, insert) > 0) {
		*write = *read;

		read--;
		write--;
		
		last--;
	}

	*write = insert;    /* Ecrit l'adresse de l'élément à insérer à la bonne place */
}

/* Trie un index de pointeur, par insertion
   @args: pointeur vers le début du vecteur de pointeur
*/
void OrderTableIndex(char **index) {
	short i = 0;
	char **sindex;          /* Pointeur vers le début de l'index */

	sindex = index;
	index++;

	while(*index != NULL) {
		OrderInsertion(sindex, *index, i);

		index++;
		i++;
	}
}