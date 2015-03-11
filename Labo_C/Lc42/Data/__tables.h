#ifndef __TABLES_HEADER
	#define __TABLES_HEADER

	#include <stdlib.h>

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

	/* Définitions */
	#define __MAX_ENTRY		100
	#define MAX_ENTRY		__MAX_ENTRY + 1

	#define MAX_YEAR_OLD    105

	typedef struct {
		char free[MAX_ENTRY];
		size_t count;
		ouvrier_t *data;

	} data_ouvrier_t;
#endif