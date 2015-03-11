#define _CRT_SECURE_NO_WARNINGS

#include "LC40-Daniel.h"
#include "__build.h"
#include "index.h"
#include "fieldsmanager.h"

/*
   Crée un node pour un champs d'affichage
   @args : (pointeur) node, le nom du champs, (pointeur) donnée ciblée, taille de l'entrée (0 = non déf.), type de champ
*/
void MkAppendField(field_t *field, char name[], void *pointer, size_t length, char type) {
	while(field->type != FIELD_EOF)
		field++;

	strcpy(field->name, name);
	field->data = pointer;
	field->length = length;
	field->type = type;

	(field+1)->type = FIELD_EOF;
}

/*
   Crée les champs pour insérer un ouvrier et demande l'entrée texte
   @args : (pointeur) nouvel ouvrier, (pointeur) une entrée d'index temporaire
*/
void InsertEntry(ouvrier_t *position, index_t *ibuffer) {
	field_t node[10];

	/* Init Node */
	node[0].type = FIELD_EOF;

	/* Create Field Node */
	MkAppendField(node, "Registre",   &position->numregistre, 0,  FIELD_INT);
	MkAppendField(node, "Nom",        position->nom,          25, FIELD_UPPER);
	MkAppendField(node, "Prenom",     position->prenom,       30, FIELD_TITLE);
	MkAppendField(node, "Rue",        position->rue,          50, FIELD_TEXT);
	MkAppendField(node, "C. Postal",  &position->codepostal,  0,  FIELD_CODEP);
	MkAppendField(node, "Ville",      position->ville,        20, FIELD_TITLE);
	MkAppendField(node, "Specialite", position->specialite,   20, FIELD_TEXT);
	MkAppendField(node, "Naissance",  &position->d_naiss,     0,  FIELD_DATE);
	MkAppendField(node, "Engagement", &position->d_engag,     0,  FIELD_DATE);

	/* Filling Node */
	FieldsProcess(node);

	/* Writing temporary Index Key */
	ibuffer->ouvrier = position;
	strcpy(ibuffer->nom, position->nom);
	strcpy(ibuffer->prenom, position->prenom);
}