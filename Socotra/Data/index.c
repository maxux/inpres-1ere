#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "index.h"
#include "misc.h"

/*
   --- TABLE: Ouvrier
*/

/* Charge un index ouvrier fichier -> ram */
/* @args: le nom du fichier index, pointeur vers l'index */
void Ouvrier_LoadIndex(char *filename, index_t *index) {
	FILE *fp;
	index_node_t *addr;

	fp = fopen(filename, "r+b");
	if(fp == NULL)
		File_Fail(filename);

	addr = index->nodes;
	if(fread(index, sizeof(index_t), 1, fp) != 1)
		File_Fail(filename);

	index->nodes = addr;
	if(fread(index->nodes, sizeof(index_node_t), MAX_OUVRIERS, fp) != MAX_OUVRIERS)
		File_Fail(filename);

	fclose(fp);
}

/* Ecrit l'index en ram, sur disque */
/* @args: le nom du fichier index, pointeur vers l'index */
void Ouvrier_SaveIndex(char *filename, index_t *index) {
	FILE *fp;

	fp = fopen(filename, "w+b");
	if(fp == NULL)
		File_Fail(filename);

	if(fwrite(index, sizeof(index_t), 1, fp) != 1)
		File_Fail(filename);

	if(fwrite(index->nodes, sizeof(index_node_t), MAX_OUVRIERS, fp) != MAX_OUVRIERS)
		File_Fail(filename);

	fclose(fp);
}

/* Crée un index avec une liste d'ouvriers */
/* @args : liste d'ouvrier, index          */
void Ouvrier_BuildIndex(char *filename, index_t *index) {
	FILE *fp;
	ouvrier_t temp;
	data_ouvrier_t base;
	size_t position, read;

	fp = fopen(filename, "r+b");
	if(fp == NULL)
		File_Fail(filename);

	strncpy(index->filename, filename, sizeof(index->filename));

	index->size = 0;
	index->skip = sizeof(data_ouvrier_t) - sizeof(base.data);

	position = index->skip;
	fseek(fp, index->skip, SEEK_SET);

	while((read = fread(&temp, sizeof(ouvrier_t), 1, fp)) != 0) {
		if(temp.numregistre != -1)
			Index_AppendRaw(index, temp.nom, temp.prenom, position);
		
		position = ftell(fp);
	}

	fclose(fp);
}

/* Affiche un popup avec les données d'un ouvrier */
/* @args : l'ouvrier                              */
void Ouvrier_ShowFormated(ouvrier_t *ouvrier) {
	dynlist_t *list;
	char temp[DYN_TEMP_LEN];

	list    = DynamicList_Create(DYNLIST_INFO);

	snprintf(temp, DYN_TEMP_LEN, "%-10s | %ld", "Numero", ouvrier->numregistre);
	DynamicList_AppendNode(list, 0, temp);

	snprintf(temp, DYN_TEMP_LEN, "%-10s | %s %s", "Ouvrier", ouvrier->nom, ouvrier->prenom);
	DynamicList_AppendNode(list, 0, temp);

	DynamicList_AppendNode(list, 0, "");
	snprintf(temp, DYN_TEMP_LEN, "%-10s | %s", "Adresse", ouvrier->rue);
	DynamicList_AppendNode(list, 0, temp);

	snprintf(temp, DYN_TEMP_LEN, "%-10s | %d - %s", " ", ouvrier->codepostal, ouvrier->ville);
	DynamicList_AppendNode(list, 0, temp);

	DynamicList_AppendNode(list, 0, "");
	snprintf(temp, DYN_TEMP_LEN, "%-10s | %02d/%02d/%02d", "Ne le", ouvrier->d_naiss.day, ouvrier->d_naiss.month, ouvrier->d_naiss.year);
	DynamicList_AppendNode(list, 0, temp);

	snprintf(temp, DYN_TEMP_LEN, "%-10s | %02d/%02d/%02d", "Engage", ouvrier->d_engag.day, ouvrier->d_engag.month, ouvrier->d_engag.year);
	DynamicList_AppendNode(list, 0, temp);
	
	DynamicList_AppendNode(list, 0, "");
	snprintf(temp, DYN_TEMP_LEN, "%-10s | %s", "Specialite", ouvrier->specialite);
	DynamicList_AppendNode(list, 0, temp);

	DynamicList_Info(list);
	DynamicList_Free(list);
}

/* Affiche le contenu d'un ouvrier dans un popup, depuis un node d'index   */
/* @args : le premier node en liste, décallage par rapport au premier node */
void Ouvrier_ShowFormated_FromFile(char *filename, dynlist_node_t *selected) {
	FILE *fp;
	ouvrier_t show;
	size_t read;

	fp = fopen(filename, "r+b");
	if(fp == NULL)
		File_Fail(filename);

	fseek(fp, selected->id, SEEK_SET);
	read = fread(&show, sizeof(ouvrier_t), 1, fp);
	if(read == 1)
		Ouvrier_ShowFormated(&show);

	fclose(fp);
}

/* Affiche les ouvriers dans l'ordre de l'index                    */
/* @args : (pointeur) debut de l'index, fonction liste contenant
           callback predefini (ou NULL pour l'affichage classique) */
void Ouvrier_ShowDataFromIndex(index_t *index, dynlist_t *precallback) {
	dynlist_t *list;
	dynlist_node_t *result = NULL;
	index_node_t *node;
	ouvrier_t element;
	size_t i;
	char temp[64];
	FILE *fp;

	if(index->size != 0) {
		node     = index->nodes;
		list     = DynamicList_Create(DYNLIST_FULL);

		fp = fopen(index->filename, "r+b");
		if(fp == NULL)
			File_Fail(index->filename);

		for(i = 0; i < index->size; i++) {
			fseek(fp, node->offset, SEEK_SET);
			if(fread(&element, sizeof(ouvrier_t), 1, fp) == 1) {
				sprintf(temp, "[%-5ld] %-15s %-15s (%02d/%02d/%02d)", element.numregistre, element.nom, element.prenom, element.d_naiss.day, element.d_naiss.month, element.d_naiss.year);
				DynamicList_AppendNode(list, node->offset, temp);

				node++;
			} 
		}

		fclose(fp);

		/* If a custom callback is defined, using it, else using Popup Callback */
		if(precallback == NULL) {
			list->callback.link  = (DYN_CALLBACK) Ouvrier_ShowFormated_FromFile;
			list->callback.param = index->filename;

		} else {
			list->callback.link  = precallback->callback.link;
			list->callback.param = precallback->callback.param;
		}

		result = DynamicList_Process(list, result);

		DynamicList_Free(list);
		DynamicList_FreeNode(result);
	} else {
		list = DynamicList_Create(DYNLIST_INFO);
		
		DynamicList_AppendNode(list, 17, "L'index est vide");
		result = DynamicList_Process(list, result);

		DynamicList_Free(list);
		DynamicList_FreeNode(result);
	}
}

/* Affiche les ouvriers dans l'ordre de la table */
/* @args : (pointeur) debut table ouvrier        */
void Ouvrier_ShowDataFromTable(char *filename) {
	dynlist_t *list;
	dynlist_node_t *result = NULL;
	ouvrier_t ouvrier;
	data_ouvrier_t base;
	size_t position, read;
	char temp[64];
	FILE *fp;

	position = sizeof(data_ouvrier_t) - sizeof(base.data);
	list     = DynamicList_Create(DYNLIST_FULL);

	fp = fopen(filename, "r+b");
	if(fp == NULL)
		File_Fail(filename);

	fseek(fp, sizeof(data_ouvrier_t) - sizeof(base.data), SEEK_SET);

	while((read = fread(&ouvrier, sizeof(ouvrier_t), 1, fp)) != 0) {
		sprintf(temp, "[%-5ld] %-15s %-15s (%02d/%02d/%02d)", ouvrier.numregistre, ouvrier.nom, ouvrier.prenom, ouvrier.d_naiss.day, ouvrier.d_naiss.month, ouvrier.d_naiss.year);
		DynamicList_AppendNode(list, position, temp);

		position = ftell(fp);
	}

	fclose(fp);

	/* Define callback to print */
	list->callback.link  = (DYN_CALLBACK) Ouvrier_ShowFormated_FromFile;
	list->callback.param = filename;

	result = DynamicList_Process(list, result);

	DynamicList_Free(list);
	DynamicList_FreeNode(result);
}

/*
   --- GENERIC INDEXING FUNCTIONS
*/
/* Tasse les élements d'un index depuis une position */
/* @args : l'index, la position                      */
void Index_Tamp(index_t *index, size_t offset) {
	index_node_t *node;
	size_t i;

	if(index->size != 0) {
		index->size--;
		node = index->nodes;
		i = 0;

		while(node->offset != offset && i++ < index->size)	/* FIXME */
			node++;

		while(i++ < index->size) {
			*node = *(node+1);
			node++;
		}
	}
}

/* Insere dans un index, un node                                             */
/* @args : (pointeur) node de début, node à insérer, indice
           du dernier node de l'index                                        */
void Index_Insert(index_node_t *start, index_node_t insert, short last) {
	index_node_t *read, *write;

	read  = start + last;   /* Pointeur de lecture */
	write = read + 1;       /* Pointeur d'écriture */

	/* Tant que l'insertion est plus bas que la case en cours, on décale */
	while(last > -1 && strcmp(read->key, insert.key) > 0) {
		*write = *read;

		read--;
		write--;
		
		last--;
	}

	while(last > -1 && strcmp(read->key, insert.key) == 0 && strcmp(read->key2, insert.key2) > 0) {
		*write = *read;

		read--;
		write--;
		
		last--;
	}

	*write = insert;    /* Ecrit l'adresse de l'élément à insérer à la bonne place */
}

/* Tri par insertion de l'index          */
/* @args : (pointeur) debut de l'index   */
void Ouvrier_IndexSort(index_t *index) {
	size_t i = 1;
	index_node_t *first;   /* Pointeur vers le début de l'index */

	first = index->nodes;

	while(i < index->size) {
		Index_Insert(first, *(first+i), i - 1);
		i++;
	}
}

/* Ajoute (non trié) d'un node dans un index                   */
/* @args : l'index, valeur de la clé, adresse du node effectif */
void Index_AppendRaw(index_t *index, char *key, char *key2, size_t offset) {
	index_node_t *node;
	size_t len;

	index->size++;
	
	if(index->nodes == NULL)
		Exit_Fail();

	node = (index->nodes + index->size - 1);

	len = strlen(key) + 1;
	strncpy(node->key, key, len);

	len = strlen(key2) + 1;
	strncpy(node->key2, key2, len);

	node->offset = offset;
}

/* Crée un index vierge              */
/* Return: l'adresse du nouvel index */
index_t * Index_Create() {
	index_t *idx;

	idx = (index_t *) malloc(sizeof(index_t));
	if(idx == NULL)
		Exit_Fail();

	idx->nodes = NULL;

	idx->size  = 0;
	idx->nodes = (index_node_t *) malloc(sizeof(index_node_t) * MAX_OUVRIERS);
	if(idx->nodes == NULL)
		Exit_Fail();

	return idx;
}

/* Libère la mémoire allouée par un index */
/* @args : l'index                        */
void Index_Free(index_t *index) {
	if(index->nodes != NULL)
		free(index->nodes);

	free(index);
}
