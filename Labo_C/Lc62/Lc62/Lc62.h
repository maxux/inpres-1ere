#ifndef __LC62_HEADER
	#define __LC62_HEADER

	typedef struct fiche_t {
		char *nom;
		short age;
		struct fiche_t *next;

	} fiche_t;

	void Affichage(fiche_t **start);
	void Insertion(fiche_t **start, fiche_t *fiche);
	void Encodage(fiche_t **start);
	void CleanList(fiche_t **start);
#endif