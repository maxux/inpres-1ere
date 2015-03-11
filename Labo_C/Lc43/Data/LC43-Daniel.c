/* General Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "__tables.h"
#include "build.h"
#include "index.h"
#include "fieldsmanager.h"
#include "postcodes.h"
#include "dynlist.h"
#include "ouvrier.h"
#include "chantier.h"
#include "disk.h"
#include "debug.h"
#ifdef WIN32
	#include "Win32Console.h"
#else
	#include "UnixConsole.h"
#endif

/*
  Prochainement (todo list):
	_ Comparaison de noms (?)
	* Annulation d'insertion
	O Gestion des accents
*/

int main(int argc, const char *argv[]) {
	index_t *idx_ouvrier;
	dynlist_t *menu;
	dynlist_node_t *choice = NULL;
	char file_index[64], file_ouvrier[64], file_chantier[64];

	/* Console Init (wconsole, globale) */
	W32Console_Init(&wconsole);

	/* Gestion du fichier ouvrier ainsi que de son index */
	idx_ouvrier = Index_Create();
	Files_Init_Check(file_index, file_ouvrier, file_chantier, idx_ouvrier);

	/* Building PostCode */
	ZipCode_Init(&zipc);

	/* Generating Menu List */
	menu = DynamicList_Create(DYNLIST_MENU);

	/* Activate Debug Mode on DynamicList */
	menu->debug = 1;

	DynamicList_AppendNode(menu, 1, "Afficher le contenu de l'index ouvrier");
	DynamicList_AppendNode(menu, 2, "Ajouter un ouvrier");
	DynamicList_AppendNode(menu, 3, "Rechercher un ouvrier");
	DynamicList_AppendNode(menu, 4, "Supprimer un ouvrier");
	DynamicList_AppendNode(menu, 5, "Editer un ouvrier");
	DynamicList_AppendNode(menu, 6, "Afficher la liste des chantiers");
	DynamicList_AppendNode(menu, 7, "Afficher la liste des chantiers avec un critère");
	DynamicList_AppendNode(menu, 8, "Ajouter un chantier");
	DynamicList_AppendNode(menu, 9, "Supprimer un chantier");
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
				/* Insere un nouvel utilisateur dans la base */
				Ouvrier_Insert(idx_ouvrier);
				break;

			case 3:
				/* Recherche un/plusieurs ouvrier(s) */
				Ouvrier_Search(idx_ouvrier);
				break;

			case 4:
				/* Supprime un/plusieurs ouvrier(s) */
				Ouvrier_Delete(idx_ouvrier);
				break;

			case 5:
				/* Edit un ouvrier */
				Ouvrier_ListEdit(idx_ouvrier);
				break;

			case 6:
				/* Affiche les chantiers */
				Chantier_Show(file_chantier, -1.0, NULL);
				break;

			case 7:
				/* Affiche les chantier avec un critère (min. cout) */
				Chantier_Show_AskCrit(file_chantier);
				break;

			case 8:
				/* Ajoute un chantier */
				Chantier_Add(file_chantier);
				break;

			case 9:
				/* Supprime un chantier */
				Chantier_Handle_Delete(file_chantier);
				break;

			case DYNLIST_DEBUG_ID:
				/* Active un Mode Debug Administratif/Concepteur */
				Debug_Menu(file_index, file_ouvrier, file_chantier);
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
