#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include "__tables.h"
#include "build.h"
#include "index.h"
#include "disk.h"
#include "dynlist.h"
#include "fieldsmanager.h"

/* Execute la vérification de fichier au démarrage du programme */
/* @args: le nom du fichier index, le nom du fichier ouvrier, le nom du fichier d'occupation, pointeur vers l'index ouvrier */
/* return: 0 toujours */
short Files_Init_Check(char *findex, char *fouvrier, char *fchantier, char *foccupe, index_t *index) {
	FILE *fp_table;
	dynlist_t *list;
	field_t *input;
	char temp[] = DEFAULT_FILENAME;
	char rebuild_occup = 0;

	list = DynamicList_Create(DYNLIST_ASK);

	/* Ouvrier Table File */
	input = Fields_Create("Chargement des tables");
	Fields_AppendNode(input, "Base de données", temp, sizeof(temp), FIELD_TEXT, FIELD_RESTRICT_ALLOW, field_dummy, NULL);
	Fields_Process(input);
	Fields_Free(input);

	snprintf(fchantier, 64, "Tables\\%s.cht", temp);
	snprintf(fouvrier,  64, "Tables\\%s.dat", temp);
	snprintf(findex,    64, "Tables\\%s.ndx", temp);
	snprintf(foccupe,   64, "Tables\\%s.pst", temp);

	/* Table ouvrier */
	fp_table = fopen(fouvrier, "rb");
	if(fp_table != NULL) {
		fclose(fp_table);

		if(DynamicList_Ask("La table (ouvrier) existe. La conserver ?")) {
			fp_table = fopen(findex, "rb");

			if(fp_table != NULL) {
				fclose(fp_table);

				if(DynamicList_Ask("L'index (ouvrier) existe. Le conserver ?")) {
					Ouvrier_LoadIndex(findex, index);

				} else {
					Ouvrier_BuildIndex(fouvrier, index);
					Ouvrier_IndexSort(index);
					Ouvrier_SaveIndex(findex, index);
				}
			} else {
				Ouvrier_BuildIndex(fouvrier, index);
				Ouvrier_IndexSort(index);
				Ouvrier_SaveIndex(findex, index);
				rebuild_occup = 1;
			}

		} else {
			Build_Ouvrier_FirstTime(fouvrier, HARDCODE_DATA);
			Ouvrier_BuildIndex(fouvrier, index);
			Ouvrier_IndexSort(index);
			Ouvrier_SaveIndex(findex, index);
			rebuild_occup = 1;
		}
	} else {
		Build_Ouvrier_FirstTime(fouvrier, 0);
		Ouvrier_BuildIndex(fouvrier, index);
		Ouvrier_SaveIndex(findex, index);
		rebuild_occup = 1;
	}

	/* Table Chantier */
	fp_table = fopen(fchantier, "rb");
	if(fp_table != NULL) {
		fclose(fp_table);

		if(!DynamicList_Ask("La table (chantiers) existe. La conserver ?")) {
			Build_Chantier_FirstTime(fchantier);
			rebuild_occup = 1;
		}
	} else {
		Build_Chantier_FirstTime(fchantier);
		rebuild_occup = 1;
	}

	/* Relation d'occupation */
	fp_table = fopen(foccupe, "rb");
	if(fp_table != NULL && !rebuild_occup) {
		fclose(fp_table);

		if(!DynamicList_Ask("Conserver les relations ouvriers/chantiers ?")) {
			fp_table = fopen(foccupe, "wb");
			fclose(fp_table);
		}
	} else {
		fp_table = fopen(foccupe, "wb");
		fclose(fp_table);
	}

	return 0;
}