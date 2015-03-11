#define _CRT_SECURE_NO_WARNINGS

#include "__tables.h"
#include "__build.h"
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

void __build_HARDCODE(data_ouvrier_t *full) {
	/* Remplis la table */
	__add_build(full, 110, "FIRKET",	 "Luc",		12,4,1987,		"Rue de Fétine, 2",		4000,	"Liège",	"coffreur",		1,5,2008);
	__add_build(full, 120, "DEMARCHE", "Jean",	24,11,1973,		"Rue du Bois, 2",		4120,	"Neupré",	"grutier",		15,1,1999);
	__add_build(full, 150, "BOVY",	 "Bernard",	12,6,1980,		"Voie Tombe, 17",		4537,	"Verlaine",	"ferrailleur",	10,5,2003);
	__add_build(full, 130, "LOURIS",	 "Pierre",	13,3,1968,		"Rue Georges, 3",		4520,	"Wanze",	"coffreur",		1,1,1987);
	__add_build(full, 170, "BOVY",	 "Alexandre", 25,10,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 180, "MAGIS",	 "Louis",	31,7,1959,		"Av. H. Monjoie, 25",	4300,	"Waremme",	"maçon",		1,2,1980);
	__add_build(full, 140, "DUPONT",	 "Marc",	16,12,1971,		"Sur le Bois 6", 		4500, 	"Huy",		"couvreur",		12,6,1997);
	__add_build(full, 160, "RENARD",	 "Michel",	24,8,1965,		"Rue Mont Falise, 115",	4500,	"Huy",		"manoeuvre",	1,9,1985);

	/* FAKE PART */
	/*__add_build(full, 171, "BOVY",	 "Hellow",   25,10,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 172, "DKKFL",	 "Yajkf",    26,9,1977, 	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 173, "POIUY",	 "Ioudf",    27,4,1977,	 "Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 174, "BCBN",	 "Iyeoiru",  30,6,1977,	 "Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 175, "ERRTY",	 "Yirjfn",   5,12,1977,	 "Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 176, "OPIUYT",	 "Bsdfksl",  13,4,1977,	 "Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 177, "QSGDDF",	 "Kamkzae",  12,1,1977,	 "Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 178, "NBVGJD",	 "Azfsdkfjsd", 17,1,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 179, "UERYEIO", "Mmlkdfsd",  20,7,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 181, "GHSKJD",	 "Bldfisdf",  13,6,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 182, "OIUERE",	 "Mqsdjfsl",  10,3,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 183, "OIUERE2", "Mqsdjfsl",  10,3,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 184, "OIUERE3", "Mqsdjfsl",  10,3,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 185, "OIUERE4", "Mqsdjfsl",  10,3,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 186, "OIUERE5", "Mqsdjfsl",  10,3,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 187, "QEIOHF",	 "Vjdhfsdio", 25,2,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 188, "QEIOHF1",	 "Vjdhfsdio", 25,2,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 189, "QEIOHF2",	 "Vjdhfsdio", 25,2,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 190, "QEIOHF3",	 "Vjdhfsdio", 25,2,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 191, "QEIOHF4",	 "Vjdhfsdio", 25,2,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 192, "QEIOHF5",	 "Vjdhfsdio", 25,2,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(full, 193, "QEIOHF9",	 "Vjdhfsdio", 25,2,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);*/
}


/* Crée une table hard-codé */
/* @args : table ouvrier    */
void __build_first_time(char *filename, short hard) {
	unsigned short i;
	ouvrier_t *table, *temp;
	data_ouvrier_t full;
	FILE *fp;

	full.data = calloc(MAX_ENTRY, sizeof(ouvrier_t));
	temp = calloc(1, sizeof(ouvrier_t));

	fp = fopen(filename, "r+b");
	if(fp == NULL) {
		fp = fopen(filename, "w+b");

		if(fp == NULL)
			File_Fail(filename);
	}

	full.count = 0;
	table = full.data;

	if(hard)
		__build_HARDCODE(&full);

	for(i = 0; i < full.count; i++)
		full.free[i] = 0;

	for(; i < MAX_ENTRY; i++)
		full.free[i] = 1;

	/* Init NULL Client (calloc-ed) */
	temp->numregistre = -1;

	for(i = full.count; i < MAX_ENTRY; i++)
		*(full.data+i) = *temp;

	if((fwrite(&full, sizeof(data_ouvrier_t), 1, fp)) != 1)
		File_Fail("Stats Write");

	fseek(fp, sizeof(data_ouvrier_t) - sizeof(full.data), SEEK_SET);

	if((fwrite(full.data, sizeof(ouvrier_t), MAX_ENTRY, fp)) != MAX_ENTRY)
		File_Fail("Data Write");

	fclose(fp);
}