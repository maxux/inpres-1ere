#ifndef __LC61_HEADER
	#define __LC61_HEADER

	typedef struct fiche_t {
		char nom[20];
		short age;
		struct fiche_t *alpha_next;
		struct fiche_t *num_next;

	} fiche_t;

	void Affichage(fiche_t **start, char ptnext);
	void Insertion(fiche_t **start_alpha, fiche_t **start_num, fiche_t *fiche);
	void Encodage(fiche_t **start_alpha, fiche_t **start_num);
	void CleanList(fiche_t **start);

	#define FOLLOW_BY_NUM     0
	#define FOLLOW_BY_ALPHA   1
#endif