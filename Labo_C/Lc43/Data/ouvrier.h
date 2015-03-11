#ifndef __OUVRIER_HEADER
	#define __OUVRIER_HEADER
	#include "index.h"
	#include "dynlist.h"
	#include "search.h"

	/* Managment */
	void Ouvrier_HandleDelete(index_t *index, dynlist_node_t *key);
	void Ouvrier_Delete(index_t *index);
	void Ouvrier_Edit(ouvrier_t *position, index_node_t *ibuffer, short restrict, index_t *index);
	void Ouvrier_HandleEdit(search_t *result, dynlist_node_t *key);
	void Ouvrier_ListEdit(index_t *index);
	void Ouvrier_Insert(index_t *index);
	void Ouvrier_Search(index_t *index);
	
	/* Input Validation */
	short Ouvrier_CheckExists(void *data, void *param);
	short Ouvrier_ListSpecialite(void *output, void *dummy);
	short Ouvrier_CompareDateEnga(void *data, void *param);
#endif