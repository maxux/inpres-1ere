#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postcodes.h"
#include "misc.h"

/* Supprime le caractère de retour à la ligne en fin de chaine */
/* @args : la chaine                                           */
void TrimName(char *data) {
	data += strlen(data) - 1;
	
	while(*data == '\n' || *data == '\r') {
		*data = '\0';
		data--;
	}
}

/* Crée un index des codes postaux   */
/* @args : structure de code postaux */
void ZipCode_BuildIndex(zipcode_t *zip) {
	size_t i, position;
	char data[128];

	i = 0;
	position = 0;

	while(fgets(data, sizeof(data), zip->fp) != NULL) {
		i++;

		zip->list = (zipcode_node_t *) realloc(zip->list, sizeof(zipcode_node_t) * i);
		zip->list[i - 1].code = atoi(data);
		zip->list[i - 1].addr = position;

		position = ftell(zip->fp);
	}
}

/* Recherche un code postal sur base du nom */
/* @args : le nom à chercher                */
void ZipCode_GetZipName(char *line) {
	char *read, *write;

	read  = line;
	write = line;

	/* Setting read pointer */
	while(*read != '\t' && *read != '\0')
		read++;

	/* Skipping Tab */
	read++;

	/* Writing */
	while(*read != '\0')
		*(write++) = *(read++);

	/* Setting EOL */
	*write = '\0';
}

/* Recupère le nom d'un code postal depuis une adresse dans la db */
/* @args : structure code postal, adresse, buffer de retour, taille du buffer */
void ZipCode_GrabName(zipcode_t *zip, size_t addr, char *buffer , size_t len) {
	/* Reading data */
	fseek(zip->fp, addr, SEEK_SET);
	fgets(buffer, len, zip->fp);

	/* Cleaning EOL */
	TrimName(buffer);

	/* Extracting Name from Line */
	ZipCode_GetZipName(buffer);

	/* Fix charset */
	w(buffer);
}

/* Retourne un pointeurs vers des nodes depuis un code postal */
/* @args : structure code postal, le code postal              */
/* Return: nodes de retour contenant les résultats            */
dynlist_node_t * ZipCode_GetListFromCode(zipcode_t *zip, short code) {
	zipcode_node_t *list;
	dynlist_t * dynlist;
	dynlist_node_t *returned = NULL;
	char buffer[128];

	list = zip->list;
	dynlist = DynamicList_Create(DYNLIST_POPUP);

	while(list->code < code)
		list++;

	while(list->code == code) {
		ZipCode_GrabName(zip, list->addr, buffer, sizeof(buffer));

		/* Appending node */
		DynamicList_AppendNode(dynlist, list->addr, buffer);

		list++;
	}

	/* Display Popup */
	returned = DynamicList_Process(dynlist, returned);
	DynamicList_Free(dynlist);

	return returned;
}

/* Initialise les code postaux    */
/* @args : structure code postaux */
void ZipCode_Init(zipcode_t *zip) {
	zip->fp = fopen(POSTCODE_FILENAME, "r");

	if(zip->fp) {
		zip->list = NULL;
		ZipCode_BuildIndex(zip);

	} else printf("Cannot load zipcodes file.\n");
}

/* Ferme un handle code postaux   */
/* @args : structure code postaux */
void ZipCode_Close(zipcode_t *zip) {
	fclose(zip->fp);
}