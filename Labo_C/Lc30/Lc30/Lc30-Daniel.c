/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :	LC30 - Tri d'un tableaiu avec un index.		*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include "Lc30-Daniel.h"
#include "Ordering.h"
#include "Display.h"
#include "Input.h"

#include <stdio.h>

int main(void) {
	char  *idx[MAX_INPUT], **index;
	char  table[MAX_INPUT][MAX_LENGTH];
	short nbname;

	index = &idx[0];

	printf("Nombre de noms: ");
	scanfshort(&nbname, MAX_INPUT);

	/* Encodage */
	EncodeNamesIndex(&table[0][0], index, nbname, MAX_LENGTH);

	/* Affichage indexé (pas encore trié) */
	printf("\n-- Show by Index --\n");
	DisplayByIndex(index);

	/* Triage */
	printf("\n>> Ordering...\n");
	OrderTableIndex(index);

	/* Affichage séquentiel */
	printf("\n-- Sequencial --\n");
	DisplayTable(&table[0][0], nbname, MAX_LENGTH);

	/* Affichage indexé (trié) */
	printf("\n-- Show by Index --\n");
	DisplayByIndex(index);

	fflush(stdin);
	getchar();

	return 0;
}