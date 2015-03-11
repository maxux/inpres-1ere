#ifndef __CHANTIER_HEADER
	#define __CHANTIER_HEADER

	void Chantier_ShowFormated(chantier_t *chantier);
	void Chantier_Handle_ShowFormated(char *filename, dynlist_node_t *selected);
	void Chantier_Show(char *filename, float max_montant, dynlist_callback_t *precallback);
	void Chantier_Show_AskCrit(char *filename);
	void Chantier_Handle_Edit(chantier_t *data, char *filename);
	void Chantier_Add(char *filename);
	void Chantier_Delete(char *filename, dynlist_node_t *selected);
	void Chantier_Handle_Delete(char *filename);
	short Chantier_CheckExists(void *data, void *param);
#endif