/* Structures */
typedef struct {
	char day;
	char month;
	short year;
} date_t;

typedef struct { 
	long numregistre;
	char nom[25];
	char prenom[30];
	char rue[50];
	int codepostal;
	char ville[20];
	char specialite[20];
	date_t d_engag;
	date_t d_naiss;
} ouvrier_t;

typedef struct {
	char nom[25];
	char prenom[30];
	ouvrier_t *ouvrier;
} index_t;

/* Définitions */
#define __MAX_ENTRY		100
#define MAX_ENTRY		__MAX_ENTRY + 1