#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "__tables.h"
#include "Win32Console.h"
#include "fieldsmanager.h"
#include "operations.h"
#include "misc.h"

/* Traite uen suppression d'un ouvrier            */
/* @args : index ouvrier, node de retour de liste */
void Ouvrier_HandleDelete(index_t *index, dynlist_node_t *key) {
	ouvrier_t *ouvrier;
	index_node_t *place;

	if(DynamicList_Ask()) {
		place   = (index_node_t *) index->nodes + key->id;
		ouvrier = place->table;

		ouvrier->numregistre = -1;
		Index_Tamp(index, key->id);

		strcpy(key->text, "(enregistrement supprimee)");
		key->id = DYNLIST_EOL; /* FIXME */
	}

	/* Note:
		La suppression multiple n'est pas encore gérée. L'index est tassé après chaque suppression
		mais le paramètre récupéré de la dynlist est le décallage par rapport à l'index original
	*/
}

/* Procédure de demande de suppresion d'ouvrier */
/* @args : index ouvrier                        */
void Ouvrier_Delete(index_t *index) {
	dynlist_t temp;

	temp.callback.link  = (DYN_CALLBACK) Ouvrier_HandleDelete;
	temp.callback.param = index;

	Ouvrier_ShowDataFromIndex(index, &temp);
}

/* Edite un ouvrier                                                        */
/* @args : pointeur vers l'ouvrier, buffer de retour (index), restrictions */
void Ouvrier_Edit(ouvrier_t *position, index_node_t *ibuffer, short restrict) {
	field_t *fields;

	ClearScreen();
	ShowConsoleCursor(1);

	/* Init Node */
	fields = Fields_Create();

	/* Create Field Node */
	Fields_AppendNode(fields, "Registre",   &position->numregistre, 0,  FIELD_INT, restrict);
	Fields_AppendNode(fields, "Nom",        position->nom,          sizeof(position->nom),        FIELD_UPPER, restrict);
	Fields_AppendNode(fields, "Prenom",     position->prenom,       sizeof(position->prenom),     FIELD_TITLE, restrict);
	Fields_AppendNode(fields, "Adresse",    position->rue,          sizeof(position->rue),        FIELD_TEXT, 1);
	Fields_AppendNode(fields, "C. Postal",  &position->codepostal,  0,  FIELD_CODEP, 1);
	Fields_AppendNode(fields, "Ville",      position->ville,        sizeof(position->ville),      FIELD_TITLE, 1);
	Fields_AppendNode(fields, "Specialite", position->specialite,   sizeof(position->specialite), FIELD_TEXT, 1);
	Fields_AppendNode(fields, "Naissance",  &position->d_naiss,     0,  FIELD_DATE, restrict);
	Fields_AppendNode(fields, "Engagement", &position->d_engag,     0,  FIELD_DATE, restrict);

	/* Filling Node */
	Fields_Process(fields);

	/* Writing temporary Index Key */
	ibuffer->table = position;

	ibuffer->key = (char *) malloc(sizeof(char) * strlen(position->nom));
	if(ibuffer->key == NULL)
		Exit_Fail();

	strcpy(ibuffer->key, position->nom);
	/* strncpy(ibuffer->prenom, position->prenom, sizeof(ibuffer->prenom)); */

	/* Clearing */
	Fields_Free(fields);
}

/* Gère une édition depuis un retour dynlist             */
/* @args : resultat de recherche, node de retour dynlist */
void Ouvrier_HandleEdit(search_t *result, dynlist_node_t *key) {
	index_node_t edited;
	Ouvrier_Edit((result->data->nodes + key->id)->table, &edited, FIELD_RESTRICT_DENIED);

	key->id = DYNLIST_EOL;
}

/* Liste les clients a éditer (avec demande d'entrée) */
/* @args : index ouvrier                              */
void Ouvrier_ListEdit(index_t *index) {
	search_t *result;
	dynlist_t callback;

	result = User_Search(index);

	if(result->nbresult > -1) {
		callback.callback.link  = (DYN_CALLBACK) Ouvrier_HandleEdit;
		callback.callback.param = result;

		Ouvrier_ShowDataFromIndex(result->data, &callback);

	} else {
		printf("Aucun resultat\n");
		getchar();
	}
	
	
	Search_Free(result);
}

/* Insert un ouvrier dans la table, met à jour l'index */
/* @args : ouvrier, index ouvrier                      */
void Ouvrier_Insert(ouvrier_t *ouvrier, index_t *index) {
	index_node_t buffer;

	if(index->size < MAX_ENTRY) {
		/* Setting up new member */
		ouvrier[index->size].numregistre = -1;

		/* Build new end */
		ouvrier[index->size + 1].numregistre = 0;

		/* Setting all at zero */
		ouvrier[index->size].nom[0]    = '\0';
		ouvrier[index->size].prenom[0] = '\0';
		ouvrier[index->size].rue[0]    = '\0';
		ouvrier[index->size].codepostal = 0;
		ouvrier[index->size].specialite[0] = '\0';
		ouvrier[index->size].ville[0]  = '\0';

		ouvrier[index->size].d_engag.day = 0;
		ouvrier[index->size].d_naiss.day = 0;

		/* Grab data */
		Ouvrier_Edit(ouvrier+index->size, &buffer, FIELD_RESTRICT_ALLOW);

		/* Updating index */
		index->nodes = (index_node_t *) realloc(index->nodes, sizeof(index_node_t) * (index->size + 1));
		if(index->nodes == NULL)
			Exit_Fail();

		Index_Insert(index->nodes, buffer, index->size - 1);
		index->size++;

	} else printf("Table pleine\n");
}

/* Recherche un ouvrier (demande d'entrée + affichage) */
/* @args : index ouvrier                               */
void Ouvrier_Search(index_t *index) {
	search_t *result;

	result = User_Search(index);

	if(result->nbresult > -1) {
		Ouvrier_ShowDataFromIndex(result->data, NULL);

	} else {
		printf(" -> Aucun resultat\n");
		getchar();
	}
	
	Search_Free(result);
}