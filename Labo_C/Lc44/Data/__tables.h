#ifndef __TABLES_HEADER
	#define __TABLES_HEADER
	#include <stdlib.h>

	/* Définitions */
	#define MAX_OUVRIERS	100
	#define MAX_CHANTIERS	20

	#define MAX_YEAR_OLD    105

	/* Structures */
	typedef struct {
		short day;
		short month;
		short year;

	} date_t;

	typedef struct { 
		long numregistre;
		char nom[25];
		char prenom[30];
		char rue[50];
		int codepostal;
		char ville[64];
		char specialite[20];
		date_t d_engag;
		date_t d_naiss;

	} ouvrier_t;

	typedef struct {
		char free[MAX_OUVRIERS];
		size_t count;
		ouvrier_t *data;

	} data_ouvrier_t;

	typedef struct {
		long numchantier;
		char nomchantier[25];
		char rue[50];
		int codepostal;
		char ville[45];
		char maitreouvrage[30];
		float montant;
		int duree;
		char gerant[3];

	} chantier_t;

	typedef struct {
		chantier_t data;
		size_t next;

	} chantier_node_t;

	typedef struct {
		size_t first;
		size_t free;
		size_t count;

	} chantier_header_t;

	typedef struct {
		long numregistre;
		long numchantier;
		date_t date;
		char heures[6];

	} estoccupe_t;
#endif