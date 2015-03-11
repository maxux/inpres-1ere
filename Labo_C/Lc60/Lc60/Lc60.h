#ifndef __LC60_HEADER
	#define __LC60_HEADER

	typedef struct fiche_t {
		char nom[20];
		short age;
		struct fiche_t *next;

	} fiche_t;

	void Affichage(fiche_t **start);
	void Insertion(fiche_t **start, fiche_t *fiche);
	void Encodage(fiche_t **start);
	void CleanList(fiche_t **start);
#endif