#define _CRT_SECURE_NO_WARNINGS

#include "LC40-Daniel.h"
#include "__build.h"
#include <string.h>

void __build(ouvrier_t *table) {
	/* Remplis la table */
	__add_build(table++, 110, "FIRKET",	 "Luc",		12,4,1987,		"Rue de Fétine, 2",		4000,	"Liège",	"coffreur",		1,5,2008);
	__add_build(table++, 120, "DEMARCHE", "Jean",	24,11,1973,		"Rue du Bois, 2",		4120,	"Neupré",	"grutier",		15,1,1999);
	__add_build(table++, 150, "BOVY",	 "Bernard",	12,6,1980,		"Voie Tombe, 17",		4537,	"Verlaine",	"ferrailleur",	10,5,2003);
	__add_build(table++, 130, "LOURIS",	 "Pierre",	13,3,1968,		"Rue Georges, 3",		4520,	"Wanze",	"coffreur",		1,1,1987);
	__add_build(table++, 170, "BOVY",	 "Alexandre", 25,10,1977,	"Rue du Centre, 15",	4557,	"Tinlot",	"maçon",		15,6,1998);
	__add_build(table++, 180, "MAGIS",	 "Louis",	31,7,1959,		"Av. H. Monjoie, 25",	4300,	"Waremme",	"maçon",		1,2,1980);
	__add_build(table++, 140, "DUPONT",	 "Marc",	16,12,1971,		"Sur le Bois 6", 		4500, 	"Huy",		"couvreur",		12,6,1997);
	__add_build(table++, 160, "RENARD",	 "Michel",	24,8,1965,		"Rue Mont Falise, 115",	4500,	"Huy",		"manoeuvre",	1,9,1985);

	/* Déclare la fin de la table */
	table->numregistre = 0;
}

void __add_build(ouvrier_t *table, long numregistre, char nom[25], char prenom[30], char d_naiss_d, char d_naiss_m, short d_naiss_y, char rue[50], int codepostal, char ville[20], char specialite[20], char d_engag_d, char d_engag_m, short d_engag_y) {
	table->numregistre = numregistre;

	strcpy(table->nom, nom);
	strcpy(table->prenom, prenom);
	strcpy(table->rue, rue);
	strcpy(table->ville, ville);
	strcpy(table->specialite, specialite);

	table->d_engag.day = d_engag_d;
	table->d_engag.month = d_engag_m;
	table->d_engag.year = d_engag_y;

	table->d_naiss.day = d_engag_d;
	table->d_naiss.month = d_engag_m;
	table->d_naiss.year = d_engag_y;

	table->codepostal = codepostal;
}
