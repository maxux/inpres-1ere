#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "LC40-Daniel.h"
#include "index.h"

/*
   Génère un index en fonction d'une table
   @args : (pointeur) debut table ouvier, (pointeur) debut index
*/
size_t BuildIndex(ouvrier_t *ouvrier, index_t *index) {
	size_t i = 0;

	while(ouvrier->numregistre != 0) {
		strcpy(index->nom, ouvrier->nom);
		strcpy(index->prenom, ouvrier->prenom);
		index->ouvrier = ouvrier;

		index++;
		ouvrier++;
		i++;
	}

	index->ouvrier = NULL;

	return i;
}

/*
   (TEMPORAIRE) Affichage formaté d'un ouvrier
   @args : pointeur vers element ouvrier
*/
void ShowFormated(ouvrier_t *ouvrier) {
	/* AFFICHAGE TEMPORAIRE */
	char temp[64];
	sprintf(temp, "%s %s", ouvrier->nom, ouvrier->prenom);

	printf("Ouvrier %-4d: %-25s | Ne: %02d/%02d/%02d - Engage: %02d/%02d/%02d\n", ouvrier->numregistre, temp, ouvrier->d_naiss.day, ouvrier->d_naiss.month, ouvrier->d_naiss.year, ouvrier->d_engag.day, ouvrier->d_engag.month, ouvrier->d_engag.year);
	printf("     Adresse: %-25s |\n", ouvrier->rue);
	printf("              %d - %-18s |\n", ouvrier->codepostal, ouvrier->ville);
	printf("  Specialite: %-25s |\n", ouvrier->specialite);
	printf("----------------------------------------+--------------------------------------\n");
}

/*
   Affiche les ouvriers dans l'ordre de l'index
   @args : (pointeur) debut de l'index
*/
void ShowDataFromIndex(index_t *index) {
	while(index->ouvrier != NULL) {
		ShowFormated(index->ouvrier);
		index++;
	}
}

/*
   Affiche les adresse des ouvriers dans l'ordre de l'index
   @args : (pointeur) debut de l'index
*/
void ShowIndexPointers(index_t *index) {
	short i = 1;

	while(index->ouvrier != NULL) {
		printf("%d) %p\n", i++, index->ouvrier);
		index++;
	}
}

/*
   Affiche les ouvriers dans l'ordre de la table
   @args : (pointeur) debut table ouvrier
*/
void ShowDataFromTable(ouvrier_t *ouvrier) {
	while(ouvrier->numregistre != 0) {
		ShowFormated(ouvrier);
		ouvrier++;
	}
}

/*
   Insere dans l'index ouvrier, un ouvrier
   @args : (pointeur) debut index, index à insérer, dernière case de l'index
*/
void Index_Insert(index_t *start, index_t insert, short last) {
	index_t *read, *write;

	read  = start + last;   /* Pointeur de lecture */
	write = read + 1;       /* Pointeur d'écriture */

	/* Tant que l'insertion est plus bas que la case en cours, on décale */
	while(last > -1 && strcmp(read->nom, insert.nom) > 0) {
		*write = *read;

		read--;
		write--;
		
		last--;
	}

	*write = insert;    /* Ecrit l'adresse de l'élément à insérer à la bonne place */
}

/*
   Tri par insertion de l'index
   @args : (pointeur) debut de l'index
*/
void Index_Sort(index_t *index) {
	short i = 0;
	index_t *sindex;          /* Pointeur vers le début de l'index */

	sindex = index;
	index++;

	while(index->ouvrier != NULL) {
		Index_Insert(sindex, *index, i);

		index++;
		i++;
	}
}