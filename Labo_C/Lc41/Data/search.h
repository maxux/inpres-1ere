#ifndef __SEARCH_HEADER
	#define __SEARCH_HEADER
	#include "__tables.h"
	#include "index.h"

	typedef struct {
		int nbresult;
		index_t *data; /* FIXME */

	} search_t;

	#define SEARCH_MAXLEN 128

	search_t * Search_Create();

	/* Prototypes */
	void Searching(index_t *index, char *target, search_t *output);
	void Search_Free(search_t *group);

	search_t * User_Search(index_t *index);
	search_t * Search_Create();
#endif