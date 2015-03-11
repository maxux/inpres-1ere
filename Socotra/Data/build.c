#define _CRT_SECURE_NO_WARNINGS

#include "__tables.h"
#include "build.h"
#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Ajoute un enregistrement dans la table ouvrier      */
/* @args : ouvrier (adresse d'insertion), nom, prenom
           jour/mois/année naissance,
		   adresse, code postal, localité,
		   jour/mois/annee engagement                   */
void __add_build(data_ouvrier_t *data, long numregistre, char nom[25], char prenom[30], char d_naiss_d, char d_naiss_m, short d_naiss_y, char rue[50], int codepostal, char ville[20], char specialite[20], char d_engag_d, char d_engag_m, short d_engag_y) {
	ouvrier_t *table;

	table = (data->data + data->count);

	table->numregistre = numregistre;

	strcpy(table->nom, nom);
	strcpy(table->prenom, prenom);
	strcpy(table->rue, rue);
	strcpy(table->ville, ville);
	strcpy(table->specialite, specialite);

	table->d_engag.day = d_engag_d;
	table->d_engag.month = d_engag_m;
	table->d_engag.year = d_engag_y;

	table->d_naiss.day = d_naiss_d;
	table->d_naiss.month = d_naiss_m;
	table->d_naiss.year = d_naiss_y;

	table->codepostal = codepostal;

	data->count++;
}

/* Hardcode une table ouvrier */
/* @args: pointeur vers une structure ouvrier */
void __build_hardcode_ouvrier(data_ouvrier_t *full) {
	/* Remplis la table */
	__add_build(full, 110, "FIRKET",	 "Luc",		12,4,1987,		"Rue de Fétine, 2",		4000,	"Liège",	"Coffreur",		1,5,2008);
	__add_build(full, 120, "DEMARCHE", "Jean",	24,11,1973,		"Rue du Bois, 2",		4120,	"Neupré",	"Grutier",		15,1,1999);
	__add_build(full, 150, "BOVY",	 "Bernard",	12,6,1980,		"Voie Tombe, 17",		4537,	"Verlaine",	"Ferrailleur",	10,5,2003);
	__add_build(full, 130, "LOUIS",	 "Pierre",	13,3,1968,		"Rue Georges, 3",		4520,	"Wanze",	"Coffreur",		1,1,1987);
	__add_build(full, 170, "BOVY",	 "Alexandre", 25,10,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"Maçon",		15,6,1998);
	__add_build(full, 180, "MAGIS",	 "Louis",	31,7,1959,		"Av. H. Monjoie, 25",	4300,	"Waremme",	"Maçon",		1,2,1980);
	__add_build(full, 140, "DUPONT",	 "Marc",	16,12,1971,		"Sur le Bois 6", 		4500, 	"Huy",		"Couvreur",		12,6,1997);
	__add_build(full, 160, "RENARD",	 "Michel",	24,8,1965,		"Rue Mont Falise, 115",	4500,	"Huy",		"Manoeuvre",	1,9,1985);
}

/* Crée une table hard-codé */
/* @args : le nom du fichier ouvrier, 0 ou 1 pour écrire l'hardcodé ou pas */
void Build_Ouvrier_FirstTime(char *filename, short hard) {
	unsigned short i;
	ouvrier_t *table, *temp;
	data_ouvrier_t full;
	FILE *fp;

	full.data = calloc(MAX_OUVRIERS, sizeof(ouvrier_t));
	temp = calloc(1, sizeof(ouvrier_t));

	fp = fopen(filename, "w+b");
	if(fp == NULL)
		File_Fail(filename);

	full.count = 0;
	table = full.data;

	if(hard)
		__build_hardcode_ouvrier(&full);

	for(i = 0; i < full.count; i++)
		full.free[i] = 0;

	for(; i < MAX_OUVRIERS; i++)
		full.free[i] = 1;

	/* Init NULL Client (calloc-ed) */
	temp->numregistre = -1;

	for(i = full.count; i < MAX_OUVRIERS; i++)
		*(full.data+i) = *temp;

	if((fwrite(&full, sizeof(data_ouvrier_t), 1, fp)) != 1)
		File_Fail("Stats Write");

	fseek(fp, sizeof(data_ouvrier_t) - sizeof(full.data), SEEK_SET);

	if((fwrite(full.data, sizeof(ouvrier_t), MAX_OUVRIERS, fp)) != MAX_OUVRIERS)
		File_Fail("Data Write");

	fclose(fp);
}

/* Crée le chainage (bidonage) chantier */
/* @args: le nom du fichier chantier */
void Build_Chantier_FirstTime(char *filename) {
	chantier_header_t header;
	chantier_node_t nodes;
	FILE *fp;
	short i;

	/* Init Header */
	header.free  = sizeof(chantier_header_t);
	header.first = 0;
	header.count = 0;

	fp = fopen(filename, "w+b");
	if(fp == NULL)
		File_Fail(filename);

	/* Writing Header */
	if(fwrite(&header, sizeof(chantier_header_t), 1, fp) != 1)
		File_Fail(filename);

	/* Writing Elements */
	nodes.data.numchantier = -1;

	for(i = 0; i < MAX_CHANTIERS - 1; i++) {
		nodes.next = sizeof(chantier_header_t) + ((i + 1) * sizeof(chantier_node_t));

		if(fwrite(&nodes, sizeof(chantier_node_t), 1, fp) != 1)
			File_Fail(filename);
	}

	/* Writing Last Element */
	nodes.data.numchantier = MAX_CHANTIERS - 1;	/* DEBUG */
	nodes.next = 0;

	if(fwrite(&nodes, sizeof(chantier_node_t), 1, fp) != 1)
		File_Fail(filename);

	fclose(fp);
}