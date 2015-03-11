#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "__tables.h"
#include "fieldsmanager.h"
#include "input.h"
#include "dynlist.h"
#include "postcodes.h"
#include "misc.h"

/*
    Attention: Module expérimental de gestion de champs texte

	Ce "module" permet de gérer un champs 'field_t' qui permet d'afficher et récupérer au clavier
	de manière (à optimisé) sécurisé.
	L'affichage sera défini par un nom de colone, une longeur maximal (texte), un type de donnée, ...
	Le contenu sera écrit directement dans une variable (multi-type) défini dans field_t

	Ce module est toujours en beta
*/

/*
   Vérifie si un caractère est alphabétique légé
   @args : un caractère
   return: 1 si valide, 0 sinon
*/
short __is_alpha(char chr) {
	short ret = 0;

	if((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z') || chr == '-' || chr == ' ' || chr == 39 || chr == '.')
		ret = 1;

	return ret;
}

/*
   Vérifie si un caractère est numérique
   @args : un caractère
   return: 1 si valide, 0 sinon
*/
short __is_num(char chr) {
	short ret = 0;

	if(chr >= '0' && chr <= '9')
		ret = 1;

	return ret;
}

/*
   Vérifie si un caractère est alphabétique étendu (guillemet, parenthèses, virgule)
   @args : un caractère
   return: 1 si valide, 0 sinon
*/
short __is_extended(char chr) {
	short ret = 0;

	if(chr == '"' || chr == '(' || chr == ')' || chr == ',' || chr == '*')
		ret = 1;

	return ret;
}

/*
   Vérifie si un caractère est alphabétique légé ou numérique (alpha numérique)
   @args : un caractère
   return: 1 si valide, 0 sinon
*/
short __is_alpha_num(char chr) {
	short ret = 0;

	if(__is_alpha(chr) || __is_num(chr))
		ret = 1;

	return ret;
}

/*
   Vérifie si un caractère est alphabétique légé, numérique ou étendu (alpha numérique étendu)
   @args : un caractère
   return: 1 si valide, 0 sinon
*/
short __is_alpha_num_extended(char chr) {
	short ret = 0;

	if(__is_alpha_num(chr) || __is_extended(chr))
		ret = 1;
	
	return ret;
}

/* Prépare l'affichage d'un champ                   */
/* @args : le contenu du champs, la taille du champ */
void PrintTextField(char *data, size_t len) {
	SetColor(FIELD_FOREGROUND, FIELD_BACKGROUND);
	printf("%-*s", len, data);
	ResetColor();
}

/* Affiche un champs date pré-formaté */
/* @args : la date a afficher         */
void PrintDateField(date_t *date) {
	SetColor(FIELD_FOREGROUND, FIELD_BACKGROUND);

	if(date->day != 0)
		printf("%02d/%02d/%04d", date->day, date->month, date->year);

	else printf("  /  /    ");

	ResetColor();
}

/*
   Permet de changer la casse en majuscule d'une chaine
   @args : (pointeur) chaine
*/
void Format_Upper(char *str) {
	while(*str != '\0') {
		*str = toupper(*str);
		str++;
	}
}

/*
   Permet de changer la casse de manière à mettre chaque première lettre d'un mot en majuscule (y compris après un -)
   @args : (pointeur) chaine
*/
void Format_Title(char *str) {
	short i = 0;

	while(*str != '\0') {
		if(i == 0) {
			*str = toupper(*str);

		} else {
			if(*str == '-' && *(str+1) != '\0') {
				*(str+1) = toupper(*(str+1));
				str++;

			} else *str = tolower(*str);
		}
		
		i++;
		str++;
	}
}

/* Affiche une erreur formaté */
/* @args : le type d'erreur   */
void Fields_ManageFail(char type) {
	COORD This;

	This = GetCursorPosition();
	SetColor(C_FORE_RED, C_BACK_BLACK);

	if(type == FIELD_FAIL_CLEAR)
		printf("         ");
	else
		if(type == FIELD_FAIL_SHOW)
			printf(" Invalide");
	
	SetColor(FIELD_FOREGROUND, FIELD_BACKGROUND);

	ChangeCurPosition(This.X, This.Y);
}

/* Permet de sélectionner et executer la gestion d'un champ */
/* @args : node                                             */
void Fields_HandleField(field_node_t *field) {
	void *output;
	dynlist_node_t *listvalue;

	output =  field->data;

	switch(field->type) {
		case FIELD_UPPER:
			if(*(char*)output != '\0')
				printf("%s", (char*) output);

			HandleFieldInput_Text(field, FIELD_ACCEPT_ALPHANUM_EXT);
			Format_Upper(field->data);
			break;

		case FIELD_TITLE:
			/* Clearing line (for CODEP rewrite) */
			printf("%-20s", " ");
			ChangeCurPosition(field->start.X, field->start.Y);

			if(*(char*)output != '\0')
				printf("%s", (char*) output);

			HandleFieldInput_Text(field, FIELD_ACCEPT_ALPHANUM);
			Format_Title(field->data);
			break;

		case FIELD_TEXT:
			if(*(char*)output != '\0')
				printf("%s", (char*) output);

			HandleFieldInput_Text(field, FIELD_ACCEPT_ALPHANUM_EXT);
			break;

		case FIELD_CODEP:
			if(*(int*)output > 0)
				printf("%d", *(int*)output);

			HandleFieldInput_Numeric(field, 1000, 9999);
			listvalue = ZipCode_GetListFromCode(&zipc, *(int*) output);

			if(listvalue->id != 0) {
				field++;
				output = field->data;
				ZipCode_GrabName(&zipc, listvalue->id, (char*) output, field->length);
			}
			break;

		case FIELD_INT:
			if(*(int*)output > 0)
				printf("%d", *(int*)output);

			HandleFieldInput_Numeric(field, 1, 65535);
			break;

		case FIELD_DATE:
			HandleFieldInput_Date(field);
			break;
	}
}

/*
   Génère et gère une liste de champ complet, leur affichage et leur assignation
   @args : (pointeur) liste de champ
*/
void Fields_Process(field_t *fields) {
	short i;               /* Counter          */
	size_t maxtitle;       /* Max len of field */
	field_node_t *prems;   /* First Field      */
	field_node_t *node;
	char tmpitoa[6];

	/* Keep first field */
	prems = fields->nodes;

	/* Parsing Fields */
	maxtitle = 0;
	node = prems;

	/* Preparing Max Length */
	for(i = 0; i < fields->nbnodes; i++) {
		if(strlen(node->name) > maxtitle)
			maxtitle = strlen(node->name);
		
		node++;
	}

	/* Display Title and Fields */
	node = prems;

	for(i = 0; i < fields->nbnodes; i++) {
		if(node->editable)
			SetColor(FIELD_FOREGROUND, FIELD_BACKGROUND);
		else
			SetColor(C_FORE_DARKGREY, FIELD_BACKGROUND);

		printf(" %-*s ", maxtitle, node->name);

		ResetColor();
		printf(" : ");

		node->start = GetCursorPosition();

		switch(node->type) {
			case FIELD_TEXT:
			case FIELD_TITLE:
			case FIELD_UPPER:
				PrintTextField(node->data, node->length);
				break;

			case FIELD_DATE:
				PrintDateField(node->data);
				break;

			case FIELD_INT:
			case FIELD_CODEP:
				if(*(int*)node->data > 0)
					__itoa(*(int*)node->data, tmpitoa);

				else *tmpitoa = '\0';

				PrintTextField(tmpitoa, 5);
				break;
		}

		printf("\n");

		node++;
	}

	node = prems;

	/* For each field, Grab input */
	for(i = 0; i < fields->nbnodes; i++) {
		if(node->editable) {
			ChangeCurPosition(node->start.X, node->start.Y);
			SetColor(FIELD_FOREGROUND, FIELD_BACKGROUND);
			
			Fields_HandleField(node);

			ResetColor();
		}

		node++;
	}

	printf("\n");
}

/* Ajoute un node pour un champs d'affichage                                 */
/* @args : liste de champs, le nom du champs, (pointeur) donnée ciblée,
           taille de l'entrée (0 = non déf.), type de champ, editable ou non */
void Fields_AppendNode(field_t *field, char name[], void *pointer, size_t length, char type, short editable) {
	field_node_t *node;
	size_t len;

	field->nbnodes++;
	field->nodes = (field_node_t *) realloc(field->nodes, sizeof(field_node_t) * field->nbnodes);
	if(field->nodes == NULL)
		Exit_Fail();

	node = field->nodes + field->nbnodes - 1;

	len = strlen(name) + 1;
	
	node->name   = (char *) malloc(sizeof(char) * len);
	if(node->name == NULL)
		Exit_Fail();

	strncpy(node->name, name, len);

	node->data     = pointer;
	node->length   = length;
	node->type     = type;
	node->editable = editable;
}

/* Crée un champs d'entrée vide             */
/* Return: l'adresse du conteneur de champs */
field_t * Fields_Create() {
	field_t *field;

	field = (field_t *) malloc(sizeof(field_t));
	if(field == NULL)
		Exit_Fail();

	field->nbnodes = 0;
	field->nodes   = NULL;

	return field;
}

/* Libère la mémoire utilisé par un conteneur de champs */
/* @args : le conteneur                                 */
void Fields_Free(field_t *field) {
	field_node_t *node;

	node = field->nodes + field->nbnodes - 1;

	while(field->nbnodes-- > 0) {
		if(node->name != NULL)
			free(node->name);

		node--;
	}
}