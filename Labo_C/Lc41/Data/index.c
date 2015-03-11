#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "index.h"
#include "misc.h"

/*
   --- TABLE: Ouvrier
*/
/* Crée un index avec une liste d'ouvriers */
/* @args : liste d'ouvrier, index          */
void Ouvrier_BuildIndex(ouvrier_t *ouvrier, index_t *index) {
	index->size = 0;

	while(ouvrier->numregistre != 0) {
		Index_AppendRaw(index, ouvrier->nom, ouvrier);
		ouvrier++;
	}
}

/* Affiche un popup avec les données d'un ouvrier */
/* @args : l'ouvrier                              */
void Ouvrier_ShowFormated(ouvrier_t *ouvrier) {
	dynlist_t *list;
	char temp[128];

	list    = DynamicList_Create(DYNLIST_INFO);

	sprintf(temp, "%-10s | %ld", "Numero", ouvrier->numregistre);
	DynamicList_AppendNode(list, 0, temp);

	sprintf(temp, "%-10s | %s %s", "Ouvrier", ouvrier->nom, ouvrier->prenom);
	DynamicList_AppendNode(list, 0, temp);

	DynamicList_AppendNode(list, 0, "");
	sprintf(temp, "%-10s | %s", "Adresse", ouvrier->rue);
	DynamicList_AppendNode(list, 0, temp);

	sprintf(temp, "%-10s | %d - %s", " ", ouvrier->codepostal, ouvrier->ville);
	DynamicList_AppendNode(list, 0, temp);

	DynamicList_AppendNode(list, 0, "");
	sprintf(temp, "%-10s | %02d/%02d/%02d", "Ne le", ouvrier->d_naiss.day, ouvrier->d_naiss.month, ouvrier->d_naiss.year);
	DynamicList_AppendNode(list, 0, temp);

	sprintf(temp, "%-10s | %02d/%02d/%02d", "Engage", ouvrier->d_engag.day, ouvrier->d_engag.month, ouvrier->d_engag.year);
	DynamicList_AppendNode(list, 0, temp);
	
	DynamicList_AppendNode(list, 0, "");
	sprintf(temp, "%-10s | %s", "Specialite", ouvrier->specialite);
	DynamicList_AppendNode(list, 0, temp);

	DynamicList_Info(list);
	DynamicList_Free(list);
}

/* Affiche le contenu d'un ouvrier dans un popup, depuis un node d'index   */
/* @args : le premier node en liste, décallage par rapport au premier node */
void Ouvrier_ShowFormated_FromIndex(index_node_t *node, dynlist_node_t *decallage) {
	Ouvrier_ShowFormated((node+decallage->id)->table);
}

/* Affiche le contenu d'un ouvrier dans un popup, depuis un node d'ouvrier */
/* @args : le premier node en liste, décallage par rapport au premier node */
void Ouvrier_ShowFormated_FromTable(ouvrier_t *ouvrier, dynlist_node_t *decallage) {
	Ouvrier_ShowFormated(ouvrier+decallage->id);
}

/* Affiche les ouvriers dans l'ordre de l'index                    */
/* @args : (pointeur) debut de l'index, fonction liste contenant
           callback predefini (ou NULL pour l'affichage classique) */
void Ouvrier_ShowDataFromIndex(index_t *index, dynlist_t *precallback) {
	dynlist_t *list;
	dynlist_node_t *result = NULL;
	index_node_t *node, *first;
	ouvrier_t *element;
	size_t position, i;
	char temp[64];

	node     = index->nodes;
	first    = index->nodes;
	position = 0;
	list     = DynamicList_Create(DYNLIST_FULL);

	for(i = 0; i < index->size; i++) {
		element = node->table;
		sprintf(temp, "[%-5ld] %-15s %-15s (%02d/%02d/%02d)", element->numregistre, element->nom, element->prenom, element->d_naiss.day, element->d_naiss.month, element->d_naiss.year);
		DynamicList_AppendNode(list, position++, temp);
		node++;
	}

	/* If a custom callback is defined, using it, else using Popup Callback */
	if(precallback == NULL) {
		list->callback.link  = (DYN_CALLBACK) Ouvrier_ShowFormated_FromIndex;
		list->callback.param = first;

	} else {
		list->callback.link  = precallback->callback.link;
		list->callback.param = precallback->callback.param;
	}

	result = DynamicList_Process(list, result);

	DynamicList_Free(list);
	DynamicList_FreeNode(result);
}

/* Affiche les ouvriers dans l'ordre de la table */
/* @args : (pointeur) debut table ouvrier        */
void Ouvrier_ShowDataFromTable(ouvrier_t *ouvrier) {
	dynlist_t *list;
	dynlist_node_t *result = NULL;
	ouvrier_t *first;
	size_t position;
	char temp[64];

	first    = ouvrier;
	position = 0;
	list     = DynamicList_Create(DYNLIST_FULL);

	while(ouvrier->numregistre != 0) {
		sprintf(temp, "[%-5ld] %-15s %-15s (%02d/%02d/%02d)", ouvrier->numregistre, ouvrier->nom, ouvrier->prenom, ouvrier->d_naiss.day, ouvrier->d_naiss.month, ouvrier->d_naiss.year);
		DynamicList_AppendNode(list, position++, temp);
		ouvrier++;
	}

	/* Define callback to print */
	list->callback.link  = (DYN_CALLBACK) Ouvrier_ShowFormated_FromTable;
	list->callback.param = first;

	result = DynamicList_Process(list, result);

	DynamicList_Free(list);
	DynamicList_FreeNode(result);
}

/*
   --- GENERIC INDEXING FUNCTIONS
*/
/* Tasse les élements d'un index depuis une position */
/* @args : l'index, la position                      */
void Index_Tamp(index_t *index, size_t position) {
	index_node_t *node;

	index->size--;
	node = index->nodes + position;

	/* printf("Position: %d   \nNode: %s   \nSize: %d   \n", position, node->key, index->size); */

	while(position++ < index->size) {
		/* printf("(%d/%d) %s -> %s\n", position, index->size, node->key, (node+1)->key); */
		*node = *(node+1);
		node++;
	}

	/* printf("DEL: %s - LAST: %s    \n", node->key, (node-1)->key);
	Index_Free_Node(node);
	getchar(); */

	index->nodes = (index_node_t *) realloc(index->nodes, sizeof(index_node_t) * (index->size + 1));
	if(index->nodes == NULL)
		Exit_Fail();
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
void Index_AppendRaw(index_t *index, char *key, void *table) {
	index_node_t *node;
	size_t len;

	index->size++;
	index->nodes = (index_node_t *) realloc(index->nodes, sizeof(index_node_t) * index->size);
	if(index->nodes == NULL)
		Exit_Fail();

	len = strlen(key) + 1;
	node = (index->nodes + index->size - 1);
	node->key = (char *) malloc(sizeof(char) * len);
	if(node->key == NULL)
		Exit_Fail();

	strncpy(node->key, key, len);
	node->table = table;
}

/* Crée un index vierge              */
/* Return: l'adresse du nouvel index */
index_t * Index_Create() {
	index_t *idx;

	idx = (index_t *) malloc(sizeof(index_t));
	if(idx == NULL)
		Exit_Fail();

	idx->size  = 0;
	idx->nodes = NULL;

	return idx;
}

/* Libère la mémoire allouée par un node (index) */
/* @args : le node                               */
void Index_Free_Node(index_node_t *node) {
	if(node->key != NULL) {
		free(node->key);
		node->key = NULL;
	}
}

/* Libère la mémoire allouée par un index */
/* @args : l'index                        */
void Index_Free(index_t *index) {
	index_node_t *node;

	if(index->nodes != NULL) {
		node = index->nodes + index->size - 1;

		while(index->size-- > 0) {
			Index_Free_Node(node);
			node--;
		}

		free(index->nodes);
	}

	free(index);
}