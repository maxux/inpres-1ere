/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :	Ex88 - Vecteur/Struct, tri.					*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "Ex88.h"
#include "Input.h"
#include "DataStruct.h"

int main(void) {
	short nbname;
	FICHE raw_data[VECT_SIZE];
	INDEX *idx_data[VECT_SIZE+1];	/* +1 => NULL */
	INDEX **pidx;					/* Pointeur vers le vecteur de pointeur */

	/* Nombre de noms */
	printf("Nombre de noms: ");
	scanfshort(&nbname, VECT_SIZE);

	/* Encodage FICHE */
	EncodeFiche(raw_data, nbname);

	/* Création de l'index */
	BuildIndex(raw_data, (*idx_data), nbname);

	/* Affichage */
	printf("\n-- Original:\n");
	PrintFicheByIndex(*idx_data);
	
	/* Tri des structures */
	pidx = idx_data;
	OrderStruct(pidx);
	
	/* Affichage */
	printf("\n-- Trie:\n");
	PrintFicheByIndex(*idx_data);

	fflush(stdin);
	getchar();

	return 0;
}