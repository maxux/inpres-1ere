#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include "__tables.h"
#include "build.h"
#include "index.h"
#include "disk.h"
#include "dynlist.h"
#include "fieldsmanager.h"

short Files_Init_Check(char *findex, char *fouvrier, char *fchantier, index_t *index) {
	FILE *fp_table, *fp_index, *fp_chantier;
	dynlist_t *list;
	field_t *input;
	short errcode = 0;
	char temp[] = DEFAULT_FILENAME;

	list = DynamicList_Create(DYNLIST_ASK);

	/* Ouvrier Table File */
	input = Fields_Create("Chargement des tables");
	Fields_AppendNode(input, "Base de données", temp, sizeof(temp), FIELD_TEXT, FIELD_RESTRICT_ALLOW, field_dummy, NULL);
	Fields_Process(input);
	Fields_Free(input);

	snprintf(fchantier, 64, "Tables\\%s.cht", temp);
	snprintf(fouvrier, 64, "Tables\\%s.dat", temp);
	snprintf(findex, 64, "Tables\\%s.ndx", temp);

	fp_table = fopen(fouvrier, "rb");
	if(fp_table != NULL) {
		fclose(fp_table);

		if(DynamicList_Ask("La table (ouvrier) existe. La conserver ?")) {
			fp_index = fopen(findex, "rb");

			if(fp_index != NULL) {
				fclose(fp_index);

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
			}

		} else {
			Build_Ouvrier_FirstTime(fouvrier, HARDCODE_DATA);
			Ouvrier_BuildIndex(fouvrier, index);
			Ouvrier_IndexSort(index);
			Ouvrier_SaveIndex(findex, index);
		}
	} else {
		Build_Ouvrier_FirstTime(fouvrier, 0);
		Ouvrier_BuildIndex(fouvrier, index);
		Ouvrier_SaveIndex(findex, index);
	}

	fp_chantier = fopen(fchantier, "rb");
	if(fp_chantier != NULL) {
		fclose(fp_chantier);

		if(!DynamicList_Ask("La table (chantiers) existe. La conserver ?")) {
			Build_Chantier_FirstTime(fchantier);
		}
	} else {
		Build_Chantier_FirstTime(fchantier);
	}

	return errcode;
}