#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include "__tables.h"
#include "__build.h"
#include "index.h"
#include "disk.h"
#include "dynlist.h"
#include "fieldsmanager.h"

short Files_Ouvrier_Check(char *findex, char *ftable, index_t *index) {
	FILE *fp_table, *fp_index;
	dynlist_t *list;
	field_t *input;
	short errcode = 0;
	char temp[] = DEFAULT_FILENAME;

	list = DynamicList_Create(DYNLIST_ASK);

	/* Ouvrier Table File */
	input = Fields_Create();
	Fields_AppendNode(input, "Table ouvier", temp, sizeof(temp), FIELD_TEXT, FIELD_RESTRICT_ALLOW);
	Fields_Process(input);
	Fields_Free(input);

	sprintf(ftable, "Tables\\%s.dat", temp);
	sprintf(findex, "Tables\\%s.ndx", temp);

	fp_table = fopen(ftable, "r+");
	if(fp_table != NULL) {
		fclose(fp_table);

		if(DynamicList_Ask("La table existe. Voulez-vous le conserver ?")) {
			fp_index = fopen(findex, "r+");

			if(fp_index != NULL) {
				fclose(fp_index);

				if(DynamicList_Ask("L'index existe. Voulez-vous le conserver ?")) {
					Ouvrier_LoadIndex(findex, index);

				} else {
					Ouvrier_BuildIndex(ftable, index);
					Ouvrier_IndexSort(index);
					Ouvrier_SaveIndex(findex, index);
				}
			} else {
				Ouvrier_BuildIndex(ftable, index);
				Ouvrier_IndexSort(index);
				Ouvrier_SaveIndex(findex, index);
			}

		} else {
			__build_first_time(ftable, 1);
			Ouvrier_BuildIndex(ftable, index);
			Ouvrier_IndexSort(index);
			Ouvrier_SaveIndex(findex, index);
		}
	} else {
		__build_first_time(ftable, 0);
		Ouvrier_BuildIndex(ftable, index);
		Ouvrier_SaveIndex(findex, index);
	}

	return errcode;
}