/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Convertisseur °C -> °F						*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR	16

void getGender(char *gender, char *keep) {
	if(gender[0] == 'h' || gender[0] == 'H') {
		strncpy(keep, "Monsieur", MAX_CHAR);

	} else if(gender[0] == 'f' || gender[0] == 'F') {
		strncpy(keep, "Madame", MAX_CHAR);

	} else strncpy(keep, "SansGenre", MAX_CHAR);
}

void getDayM(char *daym, char *keep) {
	if(daym[0] == 'm' || daym[0] == 'M') {
		strncpy(keep, "Bonjour", MAX_CHAR);

	} else if(daym[0] == 's' || daym[0] == 'S') {
		strncpy(keep, "Bonsoir", MAX_CHAR);

	} else strncpy(keep, "Plop", MAX_CHAR);
}

int main(void) {
	char *temp, *gender, *daym;

	/* Keep Gender and Moment Day on dynamic variables */
	gender = (char *) malloc(sizeof(char) * MAX_CHAR);
	daym   = (char *) malloc(sizeof(char) * MAX_CHAR);

	/* Temp will gets stdin */
	temp = (char*) malloc(sizeof(char*));

	printf("Entrez votre genre [H/F]: ");

	fflush(stdin);
	fgets(temp, sizeof(temp), stdin);
	getGender(temp, gender);

	printf("Entrez le moment de la journee [M/S]: ");
	
	fflush(stdin);
	fgets(temp, sizeof(temp), stdin);
	getDayM(temp, daym);

	printf("%s %s !\n", daym, gender);

	free(temp);
	free(daym);
	free(gender);

	fflush(stdin);
	getchar();

	return 0;
}