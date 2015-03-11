#ifndef __OCCUPATION_HEADER
	#define __OCCUPATION_HEADER

	#include "__tables.h"
	#include "index.h"

	#define O_TEMP_FILE		"Tables\\occupe.tmp"

	struct {
		char *filename;
		index_t *index;
		char *chantier;

	} typedef occupe_relation;

	struct {
		estoccupe_t *node;
		occupe_relation *relation;

	} typedef occupe_full;

	/* Management */
	void Occupation_ShowTable(char *filename, index_t *ouv_index, char *cht_file);
	void Occupation_Add(occupe_full *content);
	void Occupation_Handle_Add(occupe_relation *relation);
	short Occupation_HandleDelete(long ouvrier_id, long chantier_id, occupe_relation *relation);
#endif