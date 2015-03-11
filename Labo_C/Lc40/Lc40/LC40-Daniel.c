#include <stdio.h>
#include <string.h>

#include "LC40-Daniel.h"
#include "__build.h"
#include "index.h"
#include "fieldsmanager.h"
#include "manage.h"
#include "operations.h"

/*
  Prochainement (todo list):
	- Liste des villes par code postal
	- Affichage formaté et listé dynamiquement
	- Menu en liste dynamique
	- Blindage de date en fonction de la date courrante et d'une différence
	- Blindage en fonction d'un tableau d'entrée possible (liste dynamique ?)
	- Comparaison de noms
	- Annulation d'insertion
	- Meilleure gestion de l'affichage des erreurs d'insertion
	- Gestion des accents
	- Commentaires plus complet
*/

int main(int argc, const char *argv[]) {
	ouvrier_t ouvrier[MAX_ENTRY];   /* Liste des ouvriers */
	index_t index[MAX_ENTRY];       /* Index              */
	size_t index_size;              /* Taille de l'index  */
	char menu[1], flush;

	/* Ecriture de la table hard-codé */
	__build(ouvrier);

	/* Ecriture de l'index */
	index_size = BuildIndex(ouvrier, index);

	/* Tri de l'index */
	Index_Sort(index);

	/* Affichage de l'index */
	/* MENU TEMPORAIRE */
	do {
		ClearScreen();

		printf("Menu (temporaire): \n");
		printf("1 - Afficher le conteni de l'index\n");
		printf("2 - Afficher le contenu de la table\n");
		printf("3 - Afficher le contenu de la table\n");
		printf("4 - Ajouter un ouvrier\n");
		printf("5 - Quitter\n\n");
		printf("Choix # ");

		flush = 1;

		fflush(stdin);
		menu[0] = _getch();

		printf("\n\n");

		switch(menu[0]) {
			case '1':
				/* Affichage de l'index */
				ShowDataFromIndex(index);
				break;

			case '2':
				/* Affichage brute */
				ShowDataFromTable(ouvrier);
				break;

			case '3':
				/* Affichage pointeurs index */
				ShowIndexPointers(index);
				break;

			case '4':
				InsertOuvrier(ouvrier, index, &index_size);
				break;

			default:
				flush = 0;
				break;
		}

		if(flush) {
			fflush(stdin);
			getchar();
		}

	} while(menu[0] != '5');

	return 0; 
}