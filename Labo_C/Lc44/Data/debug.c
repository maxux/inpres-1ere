#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "__tables.h"
#include "dynlist.h"
#include "fieldsmanager.h"
#include "chantier.h"
#include "ouvrier.h"
#include "debug.h"
#include "misc.h"
#ifdef WIN32
	#include "Win32Console.h"
#else
	#include "UnixConsole.h"
#endif

/* Entre dans la gestion de debug avec un password et un menu */
/* @args: le nom du fichier index, le nom du fichier ouvrier, le nom du du fichier chantier */
void Debug_Menu(char *file_index, char *file_ouvrier, char *file_chantier) {
	dynlist_t *list;
	dynlist_node_t *choice = NULL;
	char pwd[32], key;
	short i = 0;

	ClearScreen();

	/* Asking Password */
	printf("Password: ");
	while(i < 31 && (key = _getch()) != KEYCODE_ENTER)
		pwd[i++] = key;

	pwd[i] = '\0';

	/* Checking Password */
	if(strcmp(pwd, "socotra") == 0) {
		list = DynamicList_Create(DYNLIST_MENU);
		DynamicList_AppendNode(list, 1, "Dump Chainage Chantier");
		DynamicList_AppendNode(list, 2, "Afficher le contenu de la table ouvrier (brute)");
		DynamicList_AppendNode(list, 99, "Quitter le Mode Debug");

		do {
			ClearScreen();

			printf("\n");
			PrintCenter("-- Debug Mode --");

			choice = DynamicList_Process(list, choice);

			switch(choice->id) {
				case 1:
					CurrentDebug(file_chantier);
					break;

				case 2:
					Ouvrier_ShowDataFromTable(file_ouvrier);
					break;
			}

		} while(choice->id != 99);
	}
}

/* Fonction temporaire de debuggage */
/* @args: le nom du fichier chantier dans ce cas ci */
void CurrentDebug(char *filename) {
	FILE *fp;
	chantier_node_t node;
	chantier_header_t header;
	char ok = 0;

	ClearScreen();

	fp = fopen(filename, "rb");
	if(fp == NULL)
		File_Fail(filename);

	if(fread(&header, sizeof(chantier_header_t), 1, fp) != 1)
		File_Fail(filename);

	printf("Header:\n");
	printf(" -> Count: %-4d (0x%-5x)\n", header.count, header.count);
	printf(" -> Free : %-4d (0x%-5x)\n", header.free, header.free);
	printf(" -> First: %-4d (0x%-5x)\n\n", header.first, header.first);

	getchar();

	printf("Used: \n");
	if(header.first != 0) {
		fseek(fp, header.first, SEEK_SET);
		
		while(!ok) {
			if(fread(&node, sizeof(chantier_node_t), 1, fp) != 1)
				File_Fail(filename);

			printf("Offset %-4d (0x%-5x) = %-5d - %-15s | Next -> %-4d (0x%-5x)\n", ftell(fp) - sizeof(chantier_node_t), ftell(fp) - sizeof(chantier_node_t), node.data.numchantier, node.data.nomchantier, node.next, node.next);

			if(node.next != 0)
				fseek(fp, node.next, SEEK_SET);
			else ok = 1;
		}
	}

	getchar();

	printf("\nFree:\n");
	ok = 0;

	if(header.free != 0) {
		fseek(fp, header.free, SEEK_SET);
		
		while(!ok) {
			if(fread(&node, sizeof(chantier_node_t), 1, fp) != 1)
				File_Fail(filename);

			printf("Offset: %-6d (0x%-4x) | Next -> %-6d (0x%-4x)\n", ftell(fp) - sizeof(chantier_node_t), ftell(fp) - sizeof(chantier_node_t), node.next, node.next);

			if(node.next != 0)
				fseek(fp, node.next, SEEK_SET);
			else ok = 1;
		}
	}

	getchar();
	fclose(fp);
}