#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "__tables.h"
#include "index.h"
#include "misc.h"
#include "dynlist.h"
#include "ouvrier.h"
#include "chantier.h"
#include "occupation.h"
#include "fieldsmanager.h"
#include "datemanager.h"

/* Gère une suppression de relation (demande si existant) */
/* @args: l'id ouvrier, l'id chantier, une structure relationnel */
/* return: 1 si existant et supprimé, 0 sinon */
short Occupation_HandleDelete(long ouvrier_id, long chantier_id, occupe_relation *relation) {
	short errcode;
	char found = 0;
	FILE *fp, *fp_write;
	estoccupe_t node;

	fp = fopen(relation->filename, "rb");
	if(fp == NULL)
		File_Fail(relation->filename);

	/* Read to found one match */
	while(!found && fread(&node, sizeof(estoccupe_t), 1, fp) == 1) {
		if(node.numchantier == chantier_id || node.numregistre == ouvrier_id)
			found = 1;
	}

	/* If one (or more) match */
	if(found) {
		if(DynamicList_Ask("Faire une suppression cascade des relations ?")) {
			errcode = 1;

			/* Rolling Back */
			fseek(fp, 0, SEEK_SET);

			/* Opening temp file */
			fp_write = fopen(O_TEMP_FILE, "wb");
			if(fp_write == NULL)
				File_Fail(O_TEMP_FILE);

			/* Rewriting file */
			while(fread(&node, sizeof(estoccupe_t), 1, fp) == 1) {
				if(node.numchantier != chantier_id && node.numregistre != ouvrier_id)
					if(fwrite(&node, sizeof(estoccupe_t), 1, fp_write) != 1)
						File_Fail(O_TEMP_FILE);
			}

			/* Closing Files */
			fclose(fp_write);
			fclose(fp);
			fp = NULL;

			/* Erasing current file */
			if(remove(relation->filename))
				File_Fail(relation->filename);

			/* Replacing file */
			if(rename(O_TEMP_FILE, relation->filename))
				File_Fail(relation->filename);

		} else errcode = 0;
	} else errcode = 1;

	if(fp != NULL)
		fclose(fp);

	return errcode;
}

/* Vérifie si un ouvrier ne travaille pas déjà sur un chantier a une date donnée */
/* @args: pointeur vers une structure relationnel, pointeur vers la date */
/* return: 0 si ok, 1 si déjà existant */
short Occupation_CheckDay(void *data, void *param, void *dummy) {
	short errcode = 1;
	date_t *date;
	occupe_full *content;
	estoccupe_t temp;
	ouvrier_t ouvrier;
	FILE *fp;
	size_t offset;
	char found = 0;

	content = (occupe_full *) param;
	date    = (date_t *) data;

	fp = fopen(content->relation->filename, "rb");
	if(fp == NULL)
		File_Fail(content->relation->filename);

	while(!found) {
		if(fread(&temp, sizeof(estoccupe_t), 1, fp) != 1)
			found = 1;

		/* Compare date and ouvrier */
		if(temp.numregistre == content->node->numregistre &&
		   temp.date.day    == content->node->date.day &&
		   temp.date.month  == content->node->date.month &&
		   temp.date.year   == content->node->date.year) {

			found = 1;
			errcode = 0;
		}
	}

	fclose(fp);

	/* Checking if date not < date-engagement */
	offset = Ouvrier_SearchId(content->node->numregistre, content->relation->index);

	fp = fopen(content->relation->index->filename, "rb");
	if(fp == NULL)
		File_Fail(content->relation->index->filename);

	fseek(fp, offset, SEEK_SET);
	if(fread(&ouvrier, sizeof(ouvrier_t), 1, fp) != 1)
		File_Fail(content->relation->index->filename);

	if(Date_DateToTimestamp(&content->node->date) < Date_DateToTimestamp(&ouvrier.d_engag))
		errcode = 0;

	fclose(fp);

	return errcode;
}

/* Ajoute une relation chantier/ouvrier */
/* @args: une structure relationnel */
void Occupation_Add(occupe_full *content) {
	FILE *fp;

	fp = fopen(content->relation->filename, "ab");
	if(fp == NULL)
		File_Fail(content->relation->filename);

	if(fwrite(content->node, sizeof(estoccupe_t), 1, fp) != 1)
		File_Fail(content->relation->filename);

	fclose(fp);
}

/* Prépare un ajout d'une relation chantier/ouvrier avec demande d'entrée */
/* @args: une structure relationnel */
void Occupation_Handle_Add(occupe_relation *relation) {
	estoccupe_t node;
	occupe_full content;
	dynlist_t *list;
	dynlist_node_t *result = NULL;
	chantier_header_t header;
	field_t *text;
	FILE *fp;

	ClearScreen();

	/* Setting up Pointers */
	content.node = &node;
	content.relation = relation;

	/* Preliminary check */
	/* Reading Chantier Header */
	fp = fopen(relation->chantier, "rb");
	if(fp == NULL)
		File_Fail(relation->chantier);

	if(fread(&header, sizeof(chantier_header_t), 1, fp) != 1)
		File_Fail(relation->chantier);

	fclose(fp);

	if(relation->index->size == 0 || header.count == 0) {
		list = DynamicList_Create(DYNLIST_INFO);

		if(relation->index->size == 0)
			DynamicList_AppendNode(list, 17, "Association impossible: aucun ouvriers");
		else
			DynamicList_AppendNode(list, 17, "Association impossible: aucun chantiers");

		result = DynamicList_Process(list, result);
		DynamicList_Free(list);

		

	/* Okay Let's go ! */
	} else {
		/* Creating empty element */
		node.date.day   = 0;
		node.date.month = 0;
		node.date.year  = 0;
		node.heures[0] = '\0';
		node.numregistre = 0;
		node.numchantier = 0;

		text = Fields_Create("Ajouter une relation d'occupation");

		Fields_AppendNode(text, "Ouvrier", &node.numregistre, 0, FIELD_CUSTOM, 1, Ouvrier_Handle_PickUp, relation->index);
		Fields_AppendNode(text, "Chantier", &node.numchantier, 0, FIELD_CUSTOM, 1, Chantier_Handle_PickUp, relation->chantier);
		Fields_AppendNode(text, "Date", &node.date, 0, FIELD_DATE, 1, Occupation_CheckDay, &content);
		Fields_AppendNode(text, "Nb Heures", &node.heures, sizeof(node.heures), FIELD_HOURS, 1, field_dummy, NULL);

		Fields_Process(text);
		Fields_Free(text);

		Occupation_Add(&content);
	}
}

/* Affiche la table relationnel */
/* @args: le nom du fichier relation, l'index d'ouvier, le nom du fichier chantier */
void Occupation_ShowTable(char *filename, index_t *ouv_index, char *cht_file) {
	FILE *fp, *fpo, *fpc;
	estoccupe_t node;
	dynlist_t *list;
	dynlist_node_t *result = NULL;
	ouvrier_t onode;
	chantier_node_t cnode;
	size_t offset;
	char temp[DYN_TEMP_LEN];

	list = DynamicList_Create(DYNLIST_FULL);

	/* Opening Occupe Data File */
	fp = fopen(filename, "rb");
	if(fp == NULL)
		File_Fail(filename);

	/* Opening Ouvrier Data File */
	fpo = fopen(ouv_index->filename, "rb");
	if(fpo == NULL)
		File_Fail(ouv_index->filename);

	/* Opening Chantier Data File */
	fpc = fopen(cht_file, "rb");
	if(fpc == NULL)
		File_Fail(cht_file);

	while(fread(&node, sizeof(estoccupe_t), 1, fp) == 1) {
		/* Get Offset of current Ouvrier */
		offset = Ouvrier_SearchId(node.numregistre, ouv_index);
		fseek(fpo, offset, SEEK_SET);

		if(fread(&onode, sizeof(ouvrier_t), 1, fpo) != 1)
			File_Fail(ouv_index->filename);

		/* Get Offset of current Chantier */
		offset = Chantier_SearchId(node.numchantier, cht_file);
		fseek(fpc, offset, SEEK_SET);

		if(fread(&cnode, sizeof(chantier_node_t), 1, fpc) != 1)
			File_Fail(cht_file);

		snprintf(temp, DYN_TEMP_LEN, "%02d/%02d/%02d | %-12s %-12s -> %-20s (%s hrs)", node.date.day, node.date.month, node.date.year, onode.nom, onode.prenom, cnode.data.nomchantier, node.heures);
		DynamicList_AppendNode(list, ftell(fp) - sizeof(estoccupe_t), temp);
	}

	fclose(fp);

	if(list->nbnode > 0) {
		result = DynamicList_Process(list, result);

	} else {
		DynamicList_Free(list);
		list = DynamicList_Create(DYNLIST_INFO);
		
		DynamicList_AppendNode(list, 17, "Relation vide");
		result = DynamicList_Process(list, result);
	}

	DynamicList_Free(list);
	DynamicList_FreeNode(result);
}