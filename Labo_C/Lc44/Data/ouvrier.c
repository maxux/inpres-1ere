#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "__tables.h"
#include "fieldsmanager.h"
#include "ouvrier.h"
#include "index.h"
#include "occupation.h"
#include "datemanager.h"
#include "misc.h"
#ifdef WIN32
	#include "Win32Console.h"
#else
	#include "UnixConsole.h"
#endif

/* Traite une suppression d'un ouvrier                    */
/* @args : structure relationnel, node de retour de liste */
void Ouvrier_HandleDelete(occupe_relation *relation, dynlist_node_t *key) {
	ouvrier_t ouvrier;
	data_ouvrier_t temp;
	size_t num_on_file;
	FILE *fp;

	if(DynamicList_Ask("Attention: cette opération est irréversible")) {
		fp = fopen(relation->index->filename, "r+b");
		if(fp == NULL)
			File_Fail(relation->index->filename);

		fseek(fp, key->id, SEEK_SET);

		if(fread(&ouvrier, sizeof(ouvrier_t), 1, fp) != 1)
			File_Fail(relation->index->filename);

		/* Checking EstOccupe */
		if(Occupation_HandleDelete(ouvrier.numregistre, 0, relation)) {
			ouvrier.numregistre = -1;

			fseek(fp, key->id, SEEK_SET);
			if(fwrite(&ouvrier, sizeof(ouvrier_t), 1, fp) != 1)
				File_Fail(relation->index->filename);
			
			fseek(fp, 0, SEEK_SET);
			if(fread(&temp, sizeof(data_ouvrier_t), 1, fp) == 1) {
				num_on_file = (key->id - (sizeof(data_ouvrier_t) - sizeof(temp.data))) / sizeof(ouvrier_t);
				temp.free[num_on_file] = 1;

				fseek(fp, 0, SEEK_SET);
				if(fwrite(&temp, sizeof(data_ouvrier_t), 1, fp) != 1)
					File_Fail(relation->index->filename);

			} else File_Fail(relation->index->filename);

			Index_Tamp(relation->index, key->id);

			strcpy(key->text, "(enregistrement supprimé)");
			w(key->text);
		}

		fclose(fp);
	}
}

/* Procédure de demande de suppresion d'ouvrier */
/* @args : structure relationnel                */
void Ouvrier_Delete(occupe_relation *relation) {
	dynlist_t temp;

	temp.callback.link  = (DYN_CALLBACK) Ouvrier_HandleDelete;
	temp.callback.param = relation;

	Ouvrier_ShowDataFromIndex(relation->index, &temp);
}

/* Edite un ouvrier */
/* @args : pointeur vers l'ouvrier, buffer de retour (index), restrictions, pointeur vers l'index */
void Ouvrier_Edit(ouvrier_t *position, index_node_t *ibuffer, short restrict, index_t *index) {
	field_t *fields;

	ClearScreen();
	ShowConsoleCursor(1);

	/* Init Node */
	fields = Fields_Create("Gestion d'un ouvrier");

	/* Create Field Node */
	Fields_AppendNode(fields, "Registre",   &position->numregistre, 0,  FIELD_INT, restrict, Ouvrier_CheckExists, index);
	Fields_AppendNode(fields, "Nom",        position->nom,          sizeof(position->nom),        FIELD_UPPER, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "Prénom",     position->prenom,       sizeof(position->prenom),     FIELD_TITLE, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "Adresse",    position->rue,          sizeof(position->rue),        FIELD_TEXT, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "C. Postal",  &position->codepostal,  0,  FIELD_CODEP, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "Ville",      position->ville,        sizeof(position->ville),      FIELD_TITLE, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "Spécialité", position->specialite,   sizeof(position->specialite), FIELD_CUSTOM, 1, Ouvrier_ListSpecialite, NULL);
	Fields_AppendNode(fields, "Naissance",  &position->d_naiss,     0,  FIELD_DATE, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "Engagement", &position->d_engag,     0,  FIELD_DATE, 1, Ouvrier_CompareDateEnga, &position->d_naiss);

	/* Filling Node */
	Fields_Process(fields);

	/* Updating Index */
	strcpy(ibuffer->key, position->nom);
	strcpy(ibuffer->key2, position->prenom);

	/* Clearing */
	Fields_Free(fields);
}

/* Compare la date de naissance avec la date d'engagement */
/* @args: pointeur vers la première date, pointeur vers la seconde date, pointeur null */
/* return: 0 si la date d'engagement < naissance, 1 si supérieur. */
short Ouvrier_CompareDateEnga(void *data, void *param, void *dummy) {
	short errcode = 0;
	date_t *input, *compare;
	time_t in_ts = 0, co_ts = 0;

	input = (date_t*) data;
	compare = (date_t*) param;

	in_ts = Date_DateToTimestamp(input);
	co_ts = Date_DateToTimestamp(compare);

	if(in_ts - co_ts > 409968000)	/* = 13 years old (bissextile not managed) (60*60*24*365*13) */
		errcode = 1;

	return errcode;
}

/* Affiche un popup avec les spécialitées en choix dynamique */
/* @args: pointeur vers le char de spécialité, pointeur vers la taille maximal du champs, pointeur null */
/* return: 0 (toujours) */
short Ouvrier_ListSpecialite(void *output, void *dummy, void *size) {
	dynlist_t *list;
	dynlist_node_t *result = NULL;
	char *send;
	size_t maxlen;

	send = (char*) output;
	maxlen = *(size_t*) size;

	list = DynamicList_Create(DYNLIST_POPUP);

	DynamicList_AppendNode(list, 1, "Coffreur");
	DynamicList_AppendNode(list, 2, "Ferrailleur");
	DynamicList_AppendNode(list, 3, "Couvreur");
	DynamicList_AppendNode(list, 4, "Menuisier");
	DynamicList_AppendNode(list, 5, "Maçon");
	DynamicList_AppendNode(list, 6, "Manoeuvre");
	DynamicList_AppendNode(list, 7, "Grutier");

	result = DynamicList_Process(list, result);
	printf("%s", result->text);

	strncpy(send, w(result->text), maxlen);

	DynamicList_Free(list);
	DynamicList_FreeNode(result);

	return 0;
}

/* Gère une édition depuis un retour dynlist             */
/* @args : resultat de recherche, node de retour dynlist */
void Ouvrier_HandleEdit(search_t *result, dynlist_node_t *key) {
	index_node_t edited;
	ouvrier_t edit;
	FILE *fp;

	fp = fopen(result->data->filename, "r+b");
	if(fp == NULL)
		File_Fail(result->data->filename);

	/* Seeking Current Ouvrier */
	fseek(fp, key->id, SEEK_SET);

	/* Copy Current Data */
	if(fread(&edit, sizeof(ouvrier_t), 1, fp) != 1)
		File_Fail(result->data->filename);

	/* Edit Data */
	Ouvrier_Edit(&edit, &edited, FIELD_RESTRICT_DENIED, result->data);

	/* Rewind to Current Ouvrier */
	fseek(fp, key->id, SEEK_SET);

	/* Writing back changes */
	if(fwrite(&edit, sizeof(ouvrier_t), 1, fp) != 1)
		File_Fail(result->data->filename);

	/* End Of List Process */
	key->id = DYNLIST_EOL;

	fclose(fp);
}

/* Liste les clients a éditer (avec demande d'entrée) */
/* @args : index ouvrier                              */
void Ouvrier_ListEdit(index_t *index) {
	search_t *result;
	dynlist_t *list, callback;
	dynlist_node_t *lresult = NULL;

	if(index->size > 0) {
		result = User_Search(index);

		if(result->nbresult > -1) {
			callback.callback.link  = (DYN_CALLBACK) Ouvrier_HandleEdit;
			callback.callback.param = result;

			ClearScreen();
			Ouvrier_ShowDataFromIndex(result->data, &callback);

		} else {
			ClearScreen();
			printf(" -> Aucun resultat\n");
			getchar();
		}
		
		Search_Free(result);

	} else {
		list = DynamicList_Create(DYNLIST_INFO);
		DynamicList_AppendNode(list, 17, "L'index est vide");
		lresult = DynamicList_Process(list, lresult);
		DynamicList_Free(list);
	}
}

/* Retourne l'offset du premier emplacement libre dans le fichier ouvrier */
/* @args: le nom du fichier ouvrier */
/* return: l'offset du premier emplacement libre (haha) */
size_t Ouvrier_FirstFree(char *filename) {
	data_ouvrier_t temp;
	size_t new_offset = 0;
	FILE *fp;
	short i;

	fp = fopen(filename, "r+b");

	if(fread(&temp, sizeof(data_ouvrier_t), 1, fp) == 1) {
		for(i = 0; i < MAX_OUVRIERS; i++) {
			if(temp.free[i]) {
				new_offset = (i * sizeof(ouvrier_t)) + (sizeof(data_ouvrier_t) - sizeof(temp.data));
				temp.free[i] = 0;	/* Mark position as non-free */
				i = MAX_OUVRIERS + 1;
			}
		}

	} else File_Fail(filename);

	fseek(fp, 0, SEEK_SET);
	if(fwrite(&temp, sizeof(data_ouvrier_t), 1, fp) != 1)
		File_Fail(filename);

	fclose(fp);
	
	return new_offset;
}

/* Insert un ouvrier dans la table, met à jour l'index */
/* @args : index ouvrier                               */
void Ouvrier_Insert(index_t *index) {
	index_node_t buffer;
	ouvrier_t element;
	size_t new_offset;
	FILE *fp;

	if(index->size < MAX_OUVRIERS) {
		/* Build new end */
		element.numregistre = 0;

		/* Setting all at zero */
		element.nom[0]    = '\0';
		element.prenom[0] = '\0';
		element.rue[0]    = '\0';
		element.codepostal = 0;
		element.specialite[0] = '\0';
		element.ville[0]  = '\0';

		element.d_engag.day = 0;
		element.d_naiss.day = 0;

		/* Grab data */
		Ouvrier_Edit(&element, &buffer, FIELD_RESTRICT_ALLOW, index);

		new_offset = Ouvrier_FirstFree(index->filename);

		fp = fopen(index->filename, "r+b");
		if(fp == NULL)
			File_Fail(index->filename);

		fseek(fp, new_offset, SEEK_SET);
		if(fwrite(&element, sizeof(ouvrier_t), 1, fp) != 1)
			File_Fail(index->filename);

		fclose(fp);

		/* Updating index */
		buffer.offset = new_offset;
		Index_Insert(index->nodes, buffer, index->size - 1);

		index->size++;

	} else printf("Table pleine\n");
}

/* Recherche un ouvrier (demande d'entrée + affichage) */
/* @args : index ouvrier                               */
void Ouvrier_Search(index_t *index) {
	search_t *result;
	dynlist_t *list;
	dynlist_node_t *lresult = NULL;
	size_t offs = 0;

	if(index->size > 0) {
		W32Console_SaveBuffer(&wconsole);
		result = User_Search(index);

		W32Console_RestoreBuffer(&wconsole);

		if(result->nbresult > -1) {
			strcpy(result->data->filename, index->filename);
			Ouvrier_ShowDataFromIndex(result->data, NULL);

		} else {
			ClearScreen();
			printf(" -> Aucun resultat\n");
			getchar();
		}
		
		Search_Free(result);

	} else {
		list = DynamicList_Create(DYNLIST_INFO);
		DynamicList_AppendNode(list, 17, "L'index est vide");
		lresult = DynamicList_Process(list, lresult);
		DynamicList_Free(list);
	}
}

/* Vérifie si un numregistre existe déjà dans la table */
/* @args: pointeur vers le nom du fichier ouvrier, pointeur vers le numregistre en question, pointeur null */
/* return: 0 si existe, 1 si n'existe pas */
short Ouvrier_CheckExists(void *data, void *param, void *dummy) {
	int value;
	char *filename;
	FILE *fp;
	ouvrier_t user;
	data_ouvrier_t user_nfo;
	size_t offs;
	short i, errcode = 1;

	filename = ((index_t*) param)->filename;
	value = atoi((char*) data);
	
	fp = fopen(filename, "r+b");
	if(fp == NULL)
		File_Fail(filename);

	if(fread(&user_nfo, sizeof(data_ouvrier_t), 1, fp) != 1)
		File_Fail(filename);

	for(i = 0; i < MAX_OUVRIERS; i++) {
		offs = (i * sizeof(ouvrier_t)) + sizeof(data_ouvrier_t) - sizeof(user_nfo.data);
		fseek(fp, offs, SEEK_SET);

		if(fread(&user, sizeof(ouvrier_t), 1, fp) != 1)
			File_Fail(filename);

		if(user.numregistre == value) {
			errcode = 0;
			i = MAX_OUVRIERS + 1;
		}
	}

	fclose(fp);

	return errcode;
}

/* Renvoi l'offset d'un ouvrier en fonction de son numéro de registre */
/* @args: le numregistre, le nom du fichier ouvrier */
/* return: offset dans le fichier */
size_t Ouvrier_SearchId(long numreg, index_t *index) {
	FILE *fp;
	ouvrier_t node;
	size_t offset = 0;

	fp = fopen(index->filename, "rb");
	if(fp == NULL)
		File_Fail(index->filename);

	fseek(fp, index->skip, SEEK_SET);

	while((fread(&node, sizeof(ouvrier_t), 1, fp) == 1) && !offset) {
		if(node.numregistre == numreg)
			offset = ftell(fp) - sizeof(ouvrier_t);
	}

	fclose(fp);

	return offset;
}

/* Permet de choisir un ouvrier pour l'ajout relationnel */
/* @args: l'index ouvrier */
/* return: le numregistre */
long Ouvrier_PickUp(index_t *index) {
	search_t *sresult;
	dynlist_t *list;
	dynlist_node_t *result = NULL;
	index_node_t *node;
	ouvrier_t element;
	size_t i;
	FILE *fp;
	long numreg = 0;
	char loop, temp[64];

	W32Console_SaveBuffer(&wconsole);
	printf("Appuyer sur une touche pour rechercher un ouvrier");
	_getch();

	if(index->size > 0) {
		do {
			sresult = User_Search(index);

			if(sresult->nbresult < 0) {
				loop = 1;
				Search_Free(sresult);

			} else loop = 0;
		} while(loop);

		/* Segment from Index Show Functions */
		ClearScreen();

		index = sresult->data;
		node  = index->nodes;
		list  = DynamicList_Create(DYNLIST_FULL);

		fp = fopen(index->filename, "rb");
		if(fp == NULL)
			File_Fail(index->filename);

		/* For each element, we read data on file */
		for(i = 0; i < index->size; i++) {
			fseek(fp, node->offset, SEEK_SET);
			if(fread(&element, sizeof(ouvrier_t), 1, fp) == 1) {
				sprintf(temp, "[%-5ld] %-15s %-14s (%02d/%02d/%02d)", element.numregistre, element.nom, element.prenom, element.d_naiss.day, element.d_naiss.month, element.d_naiss.year);
				DynamicList_AppendNode(list, element.numregistre, temp);
				node++;
			}
		}

		fclose(fp);

		/* Deny ESC to quit. */
		list->allow_esc = 0;

		/* Display List */
		result = DynamicList_Process(list, result);
		W32Console_RestoreBuffer(&wconsole);

		numreg = result->id;

		/* Printing current line */
		printf("%s\n", result->text);

		/* Cleaning */
		DynamicList_Free(list);
		DynamicList_FreeNode(result);
	}

	return numreg;
}

/* Prépare la demande d'ajout relationnel */
/* @args: pointeur vers l'index ouvrier, pointeur vers le résultat du field, pointeur null */
/* return: 1 (toujours) */
short Ouvrier_Handle_PickUp(void *output, void *param, void *size) {
	index_t *index;
	long *out;

	index = (index_t*) param;
	out = (long*)output;

	*out = Ouvrier_PickUp(index);

	return 1;
}