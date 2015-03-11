#ifndef __CHANTIER_HEADER
	#define __CHANTIER_HEADER

	#include "occupation.h"

	/* Managment */
	void Chantier_ShowFormated(chantier_t *chantier);
	void Chantier_Handle_ShowFormated(char *filename, dynlist_node_t *selected);
	void Chantier_Show(char *filename, float max_montant, dynlist_callback_t *precallback);
	void Chantier_Show_AskCrit(char *filename);
	void Chantier_Handle_Edit(chantier_t *data, char *filename);
	void Chantier_Add(char *filename);
	void Chantier_Delete(occupe_relation *relation, dynlist_node_t *selected);
	void Chantier_Handle_Delete(occupe_relation *relation);

	/* Search */
	dynlist_t * Chantier_Search_Node(char *key, char *filename);
	size_t Chantier_SearchId(long numch, char *filename);

	/* Input Validation */
	short Chantier_CheckExists(void *data, void *param, void *dummy);
	short Chantier_Handle_PickUp(void *output, void *param, void *size);

	/* Search/Return variables */
	long Chantier_PickUp(char *filename);
#endif