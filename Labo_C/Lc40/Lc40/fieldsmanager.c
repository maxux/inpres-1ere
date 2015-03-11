#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "LC40-Daniel.h"
#include "fieldsmanager.h"
#include "input.h"

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

	if(chr == '"' || chr == '(' || chr == ')', chr == ',')
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

/*
   Permet de préparer la console pour afficher un champ d'entrée. Ecrit du vide coloré (ou pas)
   @args : longeur d'affichage maximal
*/
void PrintTextField(size_t len) {
	size_t i;
	
	SetColor(FIELD_FOREGROUND, FIELD_BACKGROUND);

	for(i = 0; i < len; i++) {
		printf(" ");
	}

	ResetColor();
}

/*
   Permet de préparer la console pour afficher un champ date.
*/
void PrintDateField() {
	SetColor(FIELD_FOREGROUND, FIELD_BACKGROUND);
	printf("  /  /    ");

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

/*
   Affiche une erreur
*/
void PrintFail() {
	COORD This;

	This = GetCursorPosition();

	SetColor(C_BACK_RED, C_BACK_BLACK);
	printf(" Invalide");
	
	SetColor(FIELD_FOREGROUND, FIELD_BACKGROUND);

	ChangeCurPosition(This.X, This.Y);
}

/*
   Permet de sélectionner et executer la gestion d'un champ
   @args : (pointeur) node
*/
void HandleField(field_t *field) {
	switch(field->type) {
		case FIELD_UPPER:
			HandleFieldInput_Text(field, FIELD_ACCEPT_ALPHANUM);
			Format_Upper(field->data);
			break;

		case FIELD_TITLE:
			HandleFieldInput_Text(field, FIELD_ACCEPT_ALPHANUM);
			Format_Title(field->data);
			break;

		case FIELD_TEXT:
			HandleFieldInput_Text(field, FIELD_ACCEPT_ALPHANUM_EXT);
			break;

		case FIELD_CODEP:
			HandleFieldInput_Numeric(field, 1000, 9999);
			break;

		case FIELD_INT:
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
void FieldsProcess(field_t *field) {
	unsigned int i;            /* Counter          */
	size_t nbfield = 0;        /* Nb fields        */
	size_t maxtitle;           /* Max len of field */
	field_t *prems;            /* First Field      */

	/* Keep first field */
	prems = field;

	/* Checking Max Length of Titles (for aligment) */
	while(field->type != FIELD_EOF) {
		nbfield++;
		field++;
	}

	/* Parsing Fields */
	maxtitle = 0;
	field = prems;

	/* Preparing Max Length */
	for(i = 0; i < nbfield; i++) {
		if(strlen(field->name) > maxtitle)
			maxtitle = strlen(field->name);
		
		field++;
	}

	/* Display Title and Fields */
	field = prems;

	for(i = 0; i < nbfield; i++) {
		printf(" %-*s : ", maxtitle, field->name);

		field->start = GetCursorPosition();

		switch(field->type) {
			case FIELD_TEXT:
			case FIELD_TITLE:
			case FIELD_UPPER:
				PrintTextField(field->length);
				break;

			case FIELD_DATE:
				PrintDateField();
				break;

			case FIELD_INT:
				PrintTextField(10);
				break;
		}

		printf("\n");

		field++;
	}

	field = prems;

	/* For each field, Grab input */
	while(field->type != FIELD_EOF) {
		ChangeCurPosition(field->start.X, field->start.Y);
		SetColor(FIELD_FOREGROUND, FIELD_BACKGROUND);
		
		HandleField(field);

		ResetColor();
		field++;
	}

	printf("\n");
}