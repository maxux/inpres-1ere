#ifndef __OUVRIER_HEADER
	#define __OUVRIER_HEADER
	#include "index.h"
	#include "dynlist.h"
	#include "ouvrier_search.h"
	#include "occupation.h"

	/* Managment */
	void Ouvrier_HandleDelete(occupe_relation *relation, dynlist_node_t *key);
	void Ouvrier_Delete(occupe_relation *relation);
	void Ouvrier_Edit(ouvrier_t *position, index_node_t *ibuffer, short restrict, index_t *index);
	void Ouvrier_HandleEdit(search_t *result, dynlist_node_t *key);
	void Ouvrier_ListEdit(index_t *index);
	void Ouvrier_Insert(index_t *index);
	void Ouvrier_Search(index_t *index);

	/* Search */
	size_t Ouvrier_SearchId(long numreg, index_t *index);

	
	/* Input Validation */
	short Ouvrier_CheckExists(void *data, void *param, void *dummy);
	short Ouvrier_ListSpecialite(void *output, void *dummy, void *size);
	short Ouvrier_CompareDateNais(void *data, void *param, void *dummy);
	short Ouvrier_CompareDateEnga(void *data, void *param, void *dummy);
	short Ouvrier_Handle_PickUp(void *output, void *param, void *size);

	/* Search/Return variables */
	long Ouvrier_PickUp_User(index_t *index);
#endif