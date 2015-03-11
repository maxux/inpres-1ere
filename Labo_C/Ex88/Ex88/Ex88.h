#define NAME_MAX_LEN	30
#define PREN_MAX_LEN	20
#define VECT_SIZE		32

typedef struct {
	char nom[NAME_MAX_LEN];
	char prenom[PREN_MAX_LEN];
} FICHE;

typedef struct {
	char nom[NAME_MAX_LEN];
	FICHE *addr;
} INDEX;