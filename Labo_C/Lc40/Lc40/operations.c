#include <stdlib.h>
#include "LC40-Daniel.h"
#include "fieldsmanager.h"
#include "operations.h"
#include "manage.h"
#include "index.h"

/*
   Insère un ouvrier dans la table et met à jour l'index
   @args : (pointeur) debut table ouvrier, (pointeur) debut index, (pointeur) taille de l'index
*/
void InsertOuvrier(ouvrier_t *ouvrier, index_t *index, size_t *index_size) {
	index_t buffer;

	if(*(index_size) < MAX_ENTRY) {
		/* Setting up new member */
		ouvrier[*(index_size)].numregistre = -1;

		/* Build new end */
		ouvrier[*(index_size) + 1].numregistre = 0;

		/* Grab data */
		InsertEntry(&ouvrier[*index_size], &buffer);

		/* Updating index */
		Index_Insert(index, buffer, *(index_size) - 1);
		*(index_size)++;

	} else printf("Table pleine\n");
}