#ifndef __OPERATIONS_HEADER
	#define __OPERATIONS_HEADER
	#include "index.h"
	#include "dynlist.h"
	#include "search.h"

	void Ouvrier_HandleDelete(index_t *index, dynlist_node_t *key);
	void Ouvrier_Delete(index_t *index);
	void Ouvrier_Edit(ouvrier_t *position, index_node_t *ibuffer, short restrict);
	void Ouvrier_HandleEdit(search_t *result, dynlist_node_t *key);
	void Ouvrier_ListEdit(index_t *index);
	void Ouvrier_Insert(index_t *index);
	void Ouvrier_Search(index_t *index);
#endif