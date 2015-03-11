/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "Ex88.h"
#include "Input.h"
#include "DataStruct.h"

void EncodeFiche(FICHE *data, short nbname) {
	short i;

	for(i = 0; i < nbname; i++) {
		printf("Nom [%hd]: ", i);
		scanfword((data+i)->nom, NAME_MAX_LEN);

		printf("Prenom [%hd]: ", i);
		scanfword((data+i)->prenom, PREN_MAX_LEN);
	}
}

void BuildIndex(FICHE *data, INDEX *idx, short nbname) {
	short i;
	
	for(i = 0; i < nbname; i++) {
		idx->addr = data;
		strcpy(idx->nom, data->nom);
		
		data++;
		idx++;
	}

	idx->addr = NULL;
}

void PrintFiche(FICHE *data) {
	printf("[%p] %s %s\n", data, data->nom, data->prenom);
}

void PrintFicheByIndex(INDEX *idx) {
	while(idx->addr != NULL) {
		printf("[%p] %s %s\n", idx->addr, idx->addr->nom, idx->addr->prenom);
		idx++;
	}
}

/* Structure Ordering */
void InsertStruct(INDEX **index, INDEX *insert, short last) {
	INDEX **read, **write;

	read  = index + last;    /* Pointeur de lecture */
	write = read + 1;	     /* Pointeur d'écriture */

	/* Tant que l'insertion est plus bas que la case en cours, on décale */
	while(last > -1 && strcmp((*read)->nom, insert->nom) > 0) {
		*write = *read;

		read--;
		write--;
		
		last--;
	}

	*write = insert;    /* Ecrit l'adresse de l'élément à insérer à la bonne place */

	PrintFicheByIndex(*index);
}

void OrderStruct(INDEX **idx) {
	short i = 1;

	while((*idx)->addr != NULL) {
		printf("Insert: %p - %p\n", (*idx), (*idx)->addr);
		InsertStruct(idx, (*idx+i), i);
		i++;
	}
}