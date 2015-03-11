/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :	LC10 - Travail sur les vecteurs				*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include "LC10-Daniel.h"
#include "Misc.h"
#include "Design.h"
#include "OpVecteurs.h"

#include <stdio.h>

int main(void) {
	/* Déclaration du vecteur, avec une zone pour l'insertion  et une case de plus pour la sentinelle */
	int vect[VECT_SIZE + VECT_MAX_INSERT + 1];

	int key = -1;					/* Variable pour la touche pressée au menu			*/
	int vsize = 0;					/* Variable pour la taille du vecteur.				*/
	int temp, retval;				/* Variable temporaire								*/

	/* Déclaration des flags */
	short flags_vect_ordered = 1;	/* Flag: vecteur trié (vide = trié)		*/
	short flags_vect_init	 = 0;	/* Flag: vecteur initialisé (vide)		*/
	short flags_vect_full	 = 0;	/* Flag: vecteur plein					*/
	short flags_display_menu = 1;	/* Flag: afficher le menu				*/


	/* Boucle infinie sur le menu */
	while(key != MENU_EXIT) {
		if(flags_display_menu) {			/* Si on doit afficher le menu			*/
			display_menu();
			flags_display_menu = 0;			/* On ne le réaffiche plus				*/
		}

		scanfint(&key, NO_RANGE);			/* Récupération d'une touche (int)		*/

		switch(key) {
			case MENU_ENCODE:
				/* Récupération de la taille du vecteur */
				printf("Entrez la taille du vecteur (1 - %d): ", VECT_SIZE);
				scanfint(&vsize, USE_RANGE, 0, VECT_SIZE + 1);

				/* Encodage */
				if(encode_vect(vect, vsize) == CODE_SUCCESS) {
					flags_vect_init		= 1;		/* Le vecteur est bien encodé	*/
					flags_vect_ordered	= 0;		/* Le vecteur n'est pas trié	*/
					flags_vect_full		= 0;		/* Le vecteur n'est pas plein	*/
					flags_display_menu	= 1;		/* On réaffiche le menu			*/
				}
			break;

			case MENU_DISPLAY:
				if(flags_vect_init) {				/* On vérifie si le vecteur est encodé */
					display_vect(vect, vsize);

				} else error_message(MSG_VEC_EMPTY);
			break;

			case MENU_ORDER:
				if(flags_vect_init) {
					if(!flags_vect_ordered) {			/* On vérifie que le vecteur ne soit pas déjà trié...	*/
						order_vect(vect, vsize);

						flags_vect_ordered = 1;
						success_message("Vecteur trie");

					} else error_message(MSG_ALREADY_ORD);
				} else error_message(MSG_VEC_EMPTY);
			break;

			case MENU_INSERT:
				if(!flags_vect_full) {
					if(flags_vect_ordered) {
						printf("Entrez la valeur a inserer: ");
						scanfint(&temp, NO_RANGE);

						vsize = insert_vect(vect, vsize, temp);		/* On insert l'élement et on défini la nouvelle taille	*/
						printf("Element insere ! Nombre d'element: %d\n", vsize);

						if(vsize > VECT_SIZE + VECT_MAX_INSERT)			/* On vérifie si le vecteur est plein	*/
							flags_vect_full = 1;
						
						flags_vect_init = 1;

					} else error_message(MSG_NOT_ORD);
				} else error_message(MSG_VEC_EMPTY);
			break;

			case MENU_FIND:
				if(flags_vect_init) {						/* On vérifie si le vecteur est encodé		*/
					printf("Valeur a chercher: ");
					scanfint(&temp, NO_RANGE);				/* On récupère la cible de l'utilisateur	*/

					retval = find_vect(vect, vsize, temp);	/* On cherche (sentinelle)					*/

					if(retval != ERR_NOT_FOUND) {
						printf("Premiere occurence pour %d dans le vecteur a la case: %d\n", temp, retval + 1);

					} else error_message(MSG_NOT_FOUND);
				} else error_message(MSG_VEC_EMPTY);

				flags_display_menu = 0;						/* Pas besoin d'afficher le menu, réponse courte	*/
			break;

			case MENU_DSPM:
				flags_display_menu = 1;
			break;

			case MENU_EXIT:
				/* Dummy Code. Permet de ne pas afficher "Choix invalide" */
			break;

			default:
				error_message(MSG_UNK_CHOICE);
			break;
		}

		printf("\n");
	}

	/* Sortie de boucle. Fin du programme */
	printf("Exiting...\n");

	return 0;
}