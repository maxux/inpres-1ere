/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include "Design.h"
#include "LC10-Daniel.h"
#include <stdio.h>

/* Affiche le menu	*/
void display_menu(void) {
	printf("\n-- Menu principal --\n\n");
	printf("%d) Encoder des valeurs dans le vecteur\n"\
		   "%d) Afficher le contenu du vecteur\n"\
		   "%d) Trier le vecteur\n"\
		   "%d) Inserer un element dans le vecteur\n"\
		   "%d) Trouver une occurence dans le vecteur\n"\
		   "%d) Re-afficher le menu\n"\
		   "%d) Quitter\n\n", MENU_ENCODE, MENU_DISPLAY, MENU_ORDER, MENU_INSERT, MENU_FIND, MENU_DSPM, MENU_EXIT);
}

/* Affiche le contenu d'un vecteur, sous forme de tableau	*/
/* @args: pointeur sur le tableau && taille du tableau		*/
void display_vect(int *pvect, int vsize) {
	int i;

	printf("| Case | Valeur   \n"\
		   "+------+------------+\n");

	for(i = 0; i < vsize; i++) {
		if(*pvect == 0)		/* Fix: Zero non-affiché avec le formatage	*/
			printf("|%5.d | 0          |\n", i + 1);

		else printf("|%5.d | %-10d |\n", i + 1, *pvect);

		pvect++;
	}

	printf("+------+------------+\n\n");
}

/* Affiche un message formaté, en cas de réussite	*/
void success_message(char message[]) {
	printf("Okay: %s\n", message);
}

/* Affiche un message formaté en cas d'erreur		*/
void error_message(char message[]) {
	printf("Oops: %s\n", message);
}