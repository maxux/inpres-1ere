#ifndef __INDEX_HEADER
	#define __INDEX_HEADER
	#include <stdlib.h>
	#include "__tables.h"
	#include "dynlist.h"

	typedef struct {
		char *key;
		/* char prenom[30]; */
		void *table;

	} index_node_t;

	typedef struct {
		size_t size;           /* Index size (count) */
		index_node_t *nodes;   /* Nodes */

	} index_t;

	/* Prototypes */
	/* -- Ouvriers -- */
	void Ouvrier_BuildIndex(ouvrier_t *ouvrier, index_t *index);
	void Ouvrier_ShowFormated(ouvrier_t *ouvrier);
	void Ouvrier_ShowFormated_FromIndex(index_node_t *node, dynlist_node_t *decallage);
	void Ouvrier_ShowFormated_FromTable(ouvrier_t *ouvrier, dynlist_node_t *decallage);
	void Ouvrier_ShowDataFromIndex(index_t *index, dynlist_t *precallback);
	void Ouvrier_ShowDataFromTable(ouvrier_t *ouvrier);

	/* -- Generic -- */
	void Index_Tamp(index_t *index, size_t position);
	void Index_Insert(index_node_t *start, index_node_t insert, short last);
	void Ouvrier_IndexSort(index_t *index);
	void Index_AppendRaw(index_t *index, char *key, void *table);

	index_t * Index_Create();
	void Index_Free(index_t *index);
	void Index_Free_Node(index_node_t *node);
#endif