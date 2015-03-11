/* General Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "__tables.h"
#include "__build.h"
#include "index.h"
#include "fieldsmanager.h"
#include "operations.h"
#include "postcodes.h"
#include "dynlist.h"
#include "disk.h"
#ifdef WIN32
	#include "Win32Console.h"
#else
	#include "UnixConsole.h"
#endif

/*
  Prochainement (todo list):
	X Liste des villes par code postal
	X Affichage formaté et listé dynamiquement
	X Menu en liste dynamique
	X Liste dynamique: gestion des scroll
	X Blindage de date en fonction de la date courrante et d'une différence
	_ Date en fonction d'un champ
	- Blindage en fonction d'un tableau d'entrée possible (liste dynamique ?)
	- Comparaison de noms
	- Annulation d'insertion
	X Meilleure gestion de l'affichage des erreurs d'insertion
	O Gestion des accents
	X Commentaires plus complet
	X Réécrire la gestion des champs (noms fonctions + malloc)
	X Recherche: Wildcard
*/

int main(int argc, const char *argv[]) {
	index_t *idx_ouvrier;
	dynlist_t *menu;
	dynlist_node_t *choice = NULL;
	char file_index[64], file_ouvrier[64];

	/* Console Init (wconsole, globale) */
	W32Console_Init(&wconsole);

	/* Gestion du fichier ouvrier ainsi que de son index */
	idx_ouvrier = Index_Create();
	/* Files_Ouvrier_Check(idx_ouvrier, file_index, file_ouvrier); */
	Files_Ouvrier_Check(file_index, file_ouvrier, idx_ouvrier);

	/* Building PostCode */
	ZipCode_Init(&zipc);

	/* Generating Menu List */
	menu = DynamicList_Create(DYNLIST_MENU);

	DynamicList_AppendNode(menu, 1, "[Ouvrier] Afficher le contenu de l'index");
	DynamicList_AppendNode(menu, 2, "[Ouvrier] Afficher le contenu de la table (brute)");
	DynamicList_AppendNode(menu, 3, "Ajouter un ouvrier");
	DynamicList_AppendNode(menu, 4, "Rechercher un ouvrier");
	DynamicList_AppendNode(menu, 5, "Supprimer un ouvrier");
	DynamicList_AppendNode(menu, 6, "Editer un ouvrier");
	DynamicList_AppendNode(menu, 99, "Quitter");

	/* Looping on Menu */
	do {
		ClearScreen();

		printf("\n");
		PrintCenter("-- Socotra Inc --");

		choice = DynamicList_Process(menu, choice);

		switch(choice->id) {
			case 1:
				/* Affichage de l'index */
				Ouvrier_ShowDataFromIndex(idx_ouvrier, NULL);
				break;

			case 2:
				/* Affichage brute */
				Ouvrier_ShowDataFromTable(file_ouvrier);
				break;

			case 3:
				/* Insere un nouvel utilisateur dans la base */
				Ouvrier_Insert(idx_ouvrier);
				break;

			case 4:
				/* Recherche un/plusieurs ouvrier(s) */
				Ouvrier_Search(idx_ouvrier);
				break;

			case 5:
				/* Supprime un/plusieurs ouvrier(s) */
				Ouvrier_Delete(idx_ouvrier);
				break;

			case 6:
				/* Edit un ouvrier */
				Ouvrier_ListEdit(idx_ouvrier);
				break;

			default:
				break;
		}
	} while(choice->id != 99);

	/* Clearing List */
	DynamicList_FreeNode(choice);
	DynamicList_Free(menu);

	/* Saving Index */
	Ouvrier_SaveIndex(file_index, idx_ouvrier);

	/* Clearing Index */
	Index_Free(idx_ouvrier);

	/* Closing Zip Codes */
	ZipCode_Close(&zipc);

	return 0; 
}
