#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "__tables.h"
#include "dynlist.h"
#include "fieldsmanager.h"
#include "chantier.h"
#include "misc.h"
#ifdef WIN32
	#include "Win32Console.h"
#else
	#include "UnixConsole.h"
#endif

/* Affiche un popup avec les données d'un chantier */
/* @args : le chantier                             */
void Chantier_ShowFormated(chantier_t *chantier) {
	dynlist_t *list;
	char temp[DYN_TEMP_LEN];

	list    = DynamicList_Create(DYNLIST_INFO);

	snprintf(temp, 128, "%-10s | %ld", "Numero", chantier->numchantier);
	DynamicList_AppendNode(list, 0, temp);

	snprintf(temp, DYN_TEMP_LEN, "%-10s | %s", "Chantier", chantier->nomchantier);
	DynamicList_AppendNode(list, 0, temp);
	DynamicList_AppendNode(list, 0, " ");

	snprintf(temp, DYN_TEMP_LEN, "%-10s | %s", "Adresse", chantier->rue);
	DynamicList_AppendNode(list, 0, temp);

	snprintf(temp, DYN_TEMP_LEN, "%-10s | %d - %s", " ", chantier->codepostal, chantier->ville);
	DynamicList_AppendNode(list, 0, temp);

	snprintf(temp, DYN_TEMP_LEN, "%-10s | %s", "Maître", chantier->maitreouvrage);
	DynamicList_AppendNode(list, 0, temp);

	snprintf(temp, DYN_TEMP_LEN, "%-10s | %s", "Gérant", chantier->gerant);
	DynamicList_AppendNode(list, 0, temp);
	DynamicList_AppendNode(list, 0, " ");

	snprintf(temp, DYN_TEMP_LEN, "%-10s | %.3f", "Montant", chantier->montant);
	DynamicList_AppendNode(list, 0, temp);

	snprintf(temp, DYN_TEMP_LEN, "%-10s | %d", "Durée", chantier->duree);
	DynamicList_AppendNode(list, 0, temp);

	DynamicList_Info(list);
	DynamicList_Free(list);
}

void Chantier_Handle_ShowFormated(char *filename, dynlist_node_t *selected) {
	chantier_node_t nodes;
	FILE *fp;

	fp = fopen(filename, "rb");
	if(fp == NULL)
		File_Fail(filename);

	fseek(fp, selected->id, SEEK_SET);
	if(fread(&nodes, sizeof(chantier_node_t), 1, fp) != 1)
		File_Fail(filename);

	fclose(fp);

	Chantier_ShowFormated(&nodes.data);
}

void Chantier_Show(char *filename, float max_montant, dynlist_callback_t *precallback) {
	chantier_header_t header;
	chantier_node_t nodes;
	FILE *fp;
	dynlist_t *list;
	dynlist_node_t *result = NULL;
	size_t offset;
	char ok = 0;
	char temp[DYN_TEMP_LEN];

	ClearScreen();

	fp = fopen(filename, "rb");
	if(fp == NULL)
		File_Fail(filename);

	/* Reading Header */
	if(fread(&header, sizeof(chantier_header_t), 1, fp) != 1)
		File_Fail(filename);

	fseek(fp, header.first, SEEK_SET);
	offset = header.first;

	if(header.count > 0) {
		/* Preparing List */
		list = DynamicList_Create(DYNLIST_FULL);

		if(precallback == NULL) {
			list->callback.link  = Chantier_Handle_ShowFormated;
			list->callback.param = filename;
		} else {
			list->callback.link  = precallback->link;
			list->callback.param = precallback->param;
		}

		offset = header.first;
		nodes.next = 1;

		/* Skip until max_montant not reached */
		if(max_montant != -1) {
			while(!ok) {
				if(fread(&nodes, sizeof(chantier_node_t), 1, fp) != 1)
					File_Fail(filename);

				if(nodes.data.montant > max_montant) {
					/* printf("(skip) %d -> %d\n", ftell(fp) - sizeof(chantier_node_t), nodes.next); */

					if(nodes.next != 0) {
						offset = nodes.next;
						fseek(fp, nodes.next, SEEK_SET);

					} else ok = 1;
				} else {
					ok = 1;
					fseek(fp, offset, SEEK_SET);
				}
			}
		}

		/* printf("[Append] First: %d\n", offset); */

		ok = 0;

		while(!ok) {
			/* printf("(append) %d ", ftell(fp)); */
			if(fread(&nodes, sizeof(chantier_node_t), 1, fp) != 1)
				File_Fail(filename);

			/* printf("-> %d -> %d\n", ftell(fp), nodes.next); */

			snprintf(temp, DYN_TEMP_LEN, "[%-4ld] %-30s (Montant: %.2f)", nodes.data.numchantier, nodes.data.nomchantier, nodes.data.montant);
			DynamicList_AppendNode(list, ftell(fp) - sizeof(chantier_node_t), temp);

			if(nodes.next != 0) {
				fseek(fp, nodes.next, SEEK_SET);

			} else ok = 1;
		}

		/* Closing fp: fp may be handled by DynamicList_Process */
		fclose(fp);

		/* getchar(); */

		/* If no data */
		if(list->nbnode == 0) {
			DynamicList_Free(list);

			list = DynamicList_Create(DYNLIST_INFO);
			
			DynamicList_AppendNode(list, 17, "Aucun résultat");
			result = DynamicList_Process(list, result);

		} else {
			/* Show List */
			result = DynamicList_Process(list, result);
		}

		/* Clearing List */
		DynamicList_FreeNode(result);
		DynamicList_Free(list);

	} else {
		list = DynamicList_Create(DYNLIST_INFO);
		
		DynamicList_AppendNode(list, 17, "Les chantiers sont vides");
		result = DynamicList_Process(list, result);

		DynamicList_Free(list);
		DynamicList_FreeNode(result);
	}
}

void Chantier_Show_AskCrit(char *filename) {
	field_t *fields;
	float montant;

	ClearScreen();
	ShowConsoleCursor(1);

	/* Init Node */
	fields = Fields_Create("Afficher les chantiers");

	/* Create Field Node */
	Fields_AppendNode(fields, "Montant max.", &montant, 0,  FIELD_FLOAT, 1, field_dummy, NULL);
	Fields_Process(fields);
	Fields_Free(fields);

	Chantier_Show(filename, montant, NULL);
}

void Chantier_Handle_Edit(chantier_t *data, char *filename) {
	field_t *fields;

	ClearScreen();
	ShowConsoleCursor(1);

	/* Init Node */
	fields = Fields_Create("Gestion d'un chantier");

	/* Create Field Node */
	Fields_AppendNode(fields, "Numéro",    &data->numchantier,   0,  FIELD_INT, 1, Chantier_CheckExists, filename);
	Fields_AppendNode(fields, "Nom",       data->nomchantier,    sizeof(data->nomchantier),    FIELD_UPPER, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "Adresse",   data->rue,            sizeof(data->rue),            FIELD_TEXT, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "C. Postal", &data->codepostal,    0,  FIELD_CODEP, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "Ville",     data->ville,          sizeof(data->ville),          FIELD_TITLE, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "Maître",    data->maitreouvrage,  sizeof(data->maitreouvrage),  FIELD_TITLE, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "Montant",   &data->montant,       0, FIELD_FLOAT, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "Durée",     &data->duree,         0, FIELD_INT, 1, field_dummy, NULL);
	Fields_AppendNode(fields, "C. Gérant", data->gerant,         sizeof(data->gerant),         FIELD_UPPER, 1, field_dummy, NULL);

	/* Filling Node */
	Fields_Process(fields);
	Fields_Free(fields);
}

void Chantier_Add(char *filename) {
	chantier_node_t node, current;
	chantier_header_t header;
	dynlist_t *list;
	dynlist_node_t *result = NULL;
	size_t prev, new_free;
	char ok = 0;
	FILE *fp;

	fp = fopen(filename, "r+b");
	if(fp == NULL)
		File_Fail(filename);

	/* Read Header */
	if(fread(&header, sizeof(chantier_header_t), 1, fp) != 1)
		File_Fail(filename);

	/* If table not full */
	if(header.count < MAX_CHANTIERS) {
		/* Setting new empty data */
		node.data.codepostal = 0;
		node.data.duree = 0;
		node.data.gerant[0] = '\0';
		node.data.maitreouvrage[0] = '\0';
		node.data.montant = 0;
		node.data.nomchantier[0] = '\0';
		node.data.numchantier = 0;
		node.data.rue[0] = '\0';
		node.data.ville[0] = '\0';

		/* Edit empty data */
		Chantier_Handle_Edit(&node.data, filename);

		/* Reading current empty zone, writing node next free */
		fseek(fp, header.free, SEEK_SET);

		/* Reading node (to keep 'next' offset syncronized) */
		if(fread(&current, sizeof(chantier_node_t), 1, fp) != 1)
			File_Fail(filename);

		new_free = current.next;

		ok   = 0;
		prev = 0;

		current.next = 0;
		fseek(fp, header.first, SEEK_SET);

		if(header.first != 0) {
			while(!ok) {
				if(fread(&current, sizeof(chantier_node_t), 1, fp) != 1)
					File_Fail(filename);

				if(current.data.montant > node.data.montant) {
					prev = ftell(fp) - sizeof(chantier_node_t);

					/* Last Element */
					if(current.next == 0) {
						ok = 1;

					} else fseek(fp, current.next, SEEK_SET);
				} else ok = 1;
			}

			/* Position: before element to edit */
			fseek(fp, prev, SEEK_SET);
		}

		if(prev != 0) {
			if(fread(&current, sizeof(chantier_node_t), 1, fp) != 1)
				File_Fail(filename);

			node.next = current.next;		/* Previous goes to new */
			current.next = header.free;		/* New goes to old next */

			fseek(fp, prev, SEEK_SET);
			if(fwrite(&current, sizeof(chantier_node_t), 1, fp) != 1)
				File_Fail(filename);
		} else {
			node.next = header.first;
			header.first = header.free;
		}
	
		/* Update Header && Setting Offsets */
		header.count++;

		/* Seeking + switching to write mode */
		fseek(fp, header.free, SEEK_SET);
		header.free = new_free;

		/* Writing element */
		if(fwrite(&node, sizeof(chantier_node_t), 1, fp) != 1)
			File_Fail(filename);

		rewind(fp);
		if(fwrite(&header, sizeof(chantier_header_t), 1, fp) != 1)
			File_Fail(filename);

		/* getchar(); */
	} else {
		list = DynamicList_Create(DYNLIST_INFO);
		
		DynamicList_AppendNode(list, 17, "La table chantier est pleine");
		result = DynamicList_Process(list, result);

		DynamicList_Free(list);
		DynamicList_FreeNode(result);
	}

	fclose(fp);
}

void Chantier_Delete(char *filename, dynlist_node_t *selected) {
	FILE *fp;
	chantier_header_t header;
	chantier_node_t node;
	size_t replace;
	char ok = 0;

	if(DynamicList_Ask("Attention: cette opération est irréversible")) {
		fp = fopen(filename, "r+b");
		if(fp == NULL)
			File_Fail(filename);

		/* Loading Header */
		if(fread(&header, sizeof(chantier_header_t), 1, fp) != 1)
			File_Fail(filename);

		if(header.count > 0) {
			/* Reading new next element */
			fseek(fp, selected->id, SEEK_SET);
			if(fread(&node, sizeof(chantier_node_t), 1, fp) != 1)
				File_Fail(filename);

			/* Previous need to point to replace now */
			replace = node.next;
			node.next = header.free;
			node.data.numchantier = -1;

			fseek(fp, selected->id, SEEK_SET);
			if(fwrite(&node, sizeof(chantier_node_t), 1, fp) != 1)
				File_Fail(filename);

			/* Checking if it's not the first element */
			if(header.first != selected->id) {
				fseek(fp, header.first, SEEK_SET);

				/* Searching previous element */
				while(!ok) {
					if(fread(&node, sizeof(chantier_node_t), 1, fp) != 1)
						File_Fail(filename);

					if(node.next == selected->id) {
						node.next = replace;
						fseek(fp, ftell(fp) - sizeof(chantier_node_t), SEEK_SET);

						if(fwrite(&node, sizeof(chantier_node_t), 1, fp) != 1)
							File_Fail(filename);

						ok = 1;

					} else fseek(fp, node.next, SEEK_SET);
				}

			/* Well, handling header to delete first element */
			} else {
				header.first = replace;
			}

			/* Reading current Free */
			node.next = header.free;

			/* Pointing new Free */
			header.free = selected->id;

			/* Saving header */
			header.count--;

			rewind(fp);
			if(fwrite(&header, sizeof(chantier_header_t), 1, fp) != 1)
				File_Fail(filename);
		}

		fclose(fp);

		strcpy(selected->text, "(enregistrement supprimé)");
		w(selected->text);
	}

}

void Chantier_Handle_Delete(char *filename) {
	dynlist_callback_t delcallback;

	delcallback.link  = Chantier_Delete;
	delcallback.param = filename;

	Chantier_Show(filename, -1.0, &delcallback);
}

short Chantier_CheckExists(void *data, void *param) {
	FILE *fp;
	chantier_node_t node;
	chantier_header_t header;
	int id;
	char *filename, ok = 0;
	short retcode = 1;

	filename = (char*) param;
	id = atoi((char*) data);

	fp = fopen(filename, "rb");
	if(fp == NULL)
		File_Fail(filename);

	/* Reading Header */
	if(fread(&header, sizeof(chantier_header_t), 1, fp) != 1)
		File_Fail(filename);

	if(header.count != 0) {
		fseek(fp, header.first, SEEK_SET);

		while(!ok) {
			if(fread(&node, sizeof(chantier_node_t), 1, fp) != 1)
				File_Fail(filename);

			if(node.data.numchantier == id) {
				ok = 1;
				retcode = 0;

			} else {
				if(node.next != 0) {
					fseek(fp, node.next, SEEK_SET);

				} else ok = 1;
			}
		}
	}

	fclose(fp);

	return retcode;
}