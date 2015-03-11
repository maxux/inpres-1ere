#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include "Win32Console.h"
#include "dynlist.h"
#include "misc.h"

/* Affiche les bordures prévues pour les listes dynamique           */
/* @args : liste dynamique, type de direction (cf TOP_BAR, BOT_BAR) */
void DynamicList_PopupPrintBorders(dynlist_t *list, char direct) {
	size_t len;

	SetColor(list->colo_brd, list->colo_bgd);
	len = list->max_len;

	/* Left Part */
	if(direct == TOP_BARS)
		printf("%c", _BORDER_TOP_LEFT);

	else printf("%c", _BORDER_BOT_LEFT);

	/* Add Borders */
	len += 2;
	while(len-- > 0)
		printf("%c", _BORDER_HORZ_LINE);

	/* Right part */
	if(direct == TOP_BARS)
		printf("%c", _BORDER_TOP_RIGHT);

	else printf("%c", _BORDER_BOT_RIGHT);

	ResetColor();
}

/* Affiche le contenu (sans bordures) d'une liste dynamique         */
/* @args : la liste, le premier node a afficher, le nombre de node a afficher
           l'adresse d'une variable col et line, qui seront modfiés */
void DynamicList_PrintList(dynlist_t *list, dynlist_node_t *node, size_t count, short *col, short *line) {
	while(count-- > 0) {
		ChangeCurPosition(*col, *line);
		(*line)++;

		SetColor(list->colo_brd, list->colo_bgd);
		printf("%c", _BORDER_VERT_LINE);
		
		SetColor(list->colo_txt, list->colo_bgd);
		printf(" %-*s ", list->max_len, w(node->text));
		
		SetColor(list->colo_brd, list->colo_bgd);
		printf("%c\n", _BORDER_VERT_LINE);
		node++;
	}
}

/* Affiche le contenu d'une liste, avec les bordures */
/* @args : la liste, le premier node a afficher, le nombre de node a afficher
           l'adresse d'une variable col et line, qui seront modfiés */
void DynamicList_PrintWholeZone(dynlist_t *list, dynlist_node_t *node, size_t count, short *col, short *line) {
	ChangeCurPosition(*col, *line);
	(*line)++;

	/* Display Popup */
	DynamicList_PopupPrintBorders(list, TOP_BARS);
	
	DynamicList_PrintList(list, node, count, col, line);

	ChangeCurPosition(*col, *line);
	DynamicList_PopupPrintBorders(list, BOT_BARS);

	(*col)++;
	*line = list->screen_top + 1;
}

/* Surligne une ligne (selection de ligne) */
/* @args : la liste, le node à surligner, la ligne et la colone en console */
void DynamicList_MarkCurrentLine(dynlist_t *list, dynlist_node_t *node, short col, short line) {
	ChangeCurPosition(col, line);
	SetColor(list->colo_hov, list->colo_bgd);
	printf(" %-*s", list->max_len, node->text);
	ChangeCurPosition(col, line);
}

/* Démarque (réaffiche sans couleur) une ligne de la liste */
/* @args : la liste, le node a démarquer                   */
void DynamicList_UnmarkCurrentLine(dynlist_t *list, dynlist_node_t *node) {
	SetColor(list->colo_txt, list->colo_bgd);
	printf(" %-*s", list->max_len, node->text);
}


/*
    Note: An node->id set to -1 will not be validated. Use it to void interaction
*/
/* Procède à la gestion d'une liste dynamique (affichage + traitement) */
/* @args : la liste à afficher, un pointeur vers un node de retour     */
/* Return: l'adresse du node de retour                                 */
dynlist_node_t * DynamicList_Process(dynlist_t *list, dynlist_node_t *result) {
	dynlist_node_t *node, *first, *last;
	short line, col, count, scroll = 0;
	size_t delay = 0, showline = 0;
	char key[1], cont[1];

	/* Dynamic Return value */
	if(result == NULL) {
		/* TODO: If null */
		result = (dynlist_node_t *) malloc(sizeof(dynlist_node_t));
		if(result == NULL)
			Exit_Fail();

		result->text = (char *) malloc(sizeof(char) * list->max_len);
		if(result->text == NULL)
			Exit_Fail();

		result->id   = -1;
	}

	if(list->nbnode > 0) {
		/* Hiding Cursor */
		ShowConsoleCursor(0);

		/* Preparing variables */
		first = list->nodes;
		last  = first + list->nbnode - 1;

		node  = list->nodes;
		col  = (TERM_COLS / 2) - ((list->max_len + 4) / 2);
		line = list->screen_top;

		/* Preparing console */
		W32Console_SaveBuffer(&wconsole);

		/* Checking if Scroll is required */
		if(list->nbnode > (size_t) list->max_line) {
			count  = list->max_line;
			scroll = 1;

		} else count = list->nbnode;

		/* Wriring the box */
		DynamicList_PrintWholeZone(list, first, count, &col, &line);

		/* Marking current line */
		/* Menu: Check if "result" is empty. else marking previous line */
		/* if(result->id == -1 && list->type == DYNLIST_MENU) {
		} else */
		DynamicList_MarkCurrentLine(list, node, col, line);

		/* Handling Popup */
		cont[0] = 1;
		while(cont[0]) {
			fflush(stdin);
			key[0] = _getch();

			if(key[0] == 72 || key[0] == 80) {
				if(key[0] == 72 && (node > first)) {	/* If KEY UP and zone In Range */
					DynamicList_UnmarkCurrentLine(list, node);

					node--;

					/* Scroll Management */
					if(showline == 0) {
						delay--;

						/* Reset Cursors */
						col  = (TERM_COLS / 2) - ((list->max_len + 4) / 2);
						line = list->screen_top;

						/* Redraw list, with delay */
						DynamicList_PrintWholeZone(list, first + delay, count, &col, &line);

					} else showline--;
				
					DynamicList_MarkCurrentLine(list, node, col, line + showline);

				} else {
					if(key[0] == 80 && (node < last)) {	/* KEY DOWN */
						DynamicList_UnmarkCurrentLine(list, node);

						node++;

						/* Scroll Management */
						if(showline == count - 1) {
							delay++;

							/* Reset Cursors */
							col  = (TERM_COLS / 2) - ((list->max_len + 4) / 2);
							line = list->screen_top;

							/* Redraw list, with delay */
							DynamicList_PrintWholeZone(list, first + delay, count, &col, &line);

						} else showline++;

						DynamicList_MarkCurrentLine(list, node, col, line + showline);
					}
				}

			/* Else Key pressed are not arrows */
			} else {
					/* Check ENTER key */
					if(key[0] == KEYCODE_ENTER && node->id != -1) {
						result->id = node->id;
						strncpy(result->text, node->text, list->max_len);

						/* Callback function if defined */
						if(list->callback.link != NULL) {
							list->callback.link(list->callback.param, (void *) result);

							/* Checking for result editing */
							if(result->id != DYNLIST_EOL) {
								if(strncmp(node->text, result->text, list->max_len) != 0 || node->id != result->id) {
									strncpy(node->text, result->text, list->max_len);
									node->id = result->id;
									DynamicList_MarkCurrentLine(list, node, col, line + showline); /* Redraw Line */
								}
							} else cont[0] = 0;
							
							/* Reset Cursor State */
							ShowConsoleCursor(0);

						} else cont[0] = 0;
					} else {
						if(key[0] == KEYCODE_ESC) {
							result->id = 0;
							strncpy(result->text, "\0", list->max_len);
							cont[0] = 0;
						}
					}
			}
		}

		/* Clearing */
		ResetColor();
		W32Console_RestoreBuffer(&wconsole);
		ShowConsoleCursor(1);

	} else result->id = 0;

	return result;
}

/* Affiche une liste sous forme de 'popup' */
/* @args : la liste                        */
void DynamicList_Info(dynlist_t *list) {
	dynlist_node_t *node;
	short line, col;
	char key[1];

	if(list->nbnode > 0) {
		/* Preparing variables */
		node = list->nodes;
		col  = (TERM_COLS / 2) - ((list->max_len + 4) / 2);
		line = list->screen_top;

		/* Preparing console */
		W32Console_SaveBuffer(&wconsole);
		ChangeCurPosition(col, line);
		ShowConsoleCursor(0);

		/* Display Popup */
		DynamicList_PrintWholeZone(list, node, list->nbnode, &col, &line);
		

		/* Waiting ENTER Key */
		do {
			key[0] = _getch();

		} while(key[0] != KEYCODE_ENTER);

		/* Clearing */
		ResetColor();
		W32Console_RestoreBuffer(&wconsole);
		ShowConsoleCursor(1);
	}
}

/* Traite une liste de demande de confirmation */
/* Return: 1 si validé, 0 si annulé            */
short DynamicList_Ask() {
	dynlist_t *list;
	short line, col, retcode;
	char key[1];

	list = DynamicList_Create(DYNLIST_ASK);
	DynamicList_AppendNode(list, 0, "Etes-vous sur de vouloir effectuer cette action ?");
	DynamicList_AppendNode(list, 0, " -> Appuyer sur ENTER pour confirmer");
	DynamicList_AppendNode(list, 0, " -> Appuyer sur ESCAPE pour annuler");

	/* Preparing variables */
	col  = (TERM_COLS / 2) - ((list->max_len + 4) / 2);
	line = list->screen_top;

	/* Preparing console */
	W32Console_SaveBuffer(&wconsole);
	ChangeCurPosition(col, line);
	ShowConsoleCursor(0);

	/* Display Popup */
	DynamicList_PrintWholeZone(list, list->nodes, list->nbnode, &col, &line);

	/* Waiting ENTER Key */
	do {
		key[0] = _getch();

	} while(key[0] != KEYCODE_ENTER && key[0] != KEYCODE_ESC);

	/* Clearing */
	DynamicList_Free(list);

	ResetColor();
	W32Console_RestoreBuffer(&wconsole);
	ShowConsoleCursor(1);

	if(key[0] == KEYCODE_ENTER)
		retcode = 1;

	else retcode = 0;

	return retcode;
}

/* Ajoute un node à une liste                                */
/* @args : la liste, l'identifiant du node, le texte du node */
void DynamicList_AppendNode(dynlist_t *list, size_t id, char *text) {
	dynlist_node_t *node;
	char *output;

	/* Making new node, re-allocating nodes */
	list->nbnode++;
	list->nodes = (dynlist_node_t *) realloc(list->nodes, sizeof(dynlist_node_t) * list->nbnode);
	if(list->nodes == NULL)
		Exit_Fail();

	node = list->nodes + list->nbnode - 1;

	/* Setting ID */
	node->id = id;

	/* Setting Text */
	node->text = (char *) malloc(sizeof(char) *	list->max_len);
	if(node->text == NULL)
		Exit_Fail();

	output = node->text;

	/* Writing text */
	strncpy(output, text, list->max_len);
	output += list->max_len - 1;
	*output = '\0';
}

/* Crée une liste dynamique vierge            */
/* @args : type de liste (cf DYNLIST_xx)      */
/* Return: l'adresse de la liste vierge créée */
dynlist_t * DynamicList_Create(char type) {
	dynlist_t *dynlist;

	dynlist = (dynlist_t *) malloc(sizeof(dynlist_t));
	if(dynlist == NULL)
		Exit_Fail();

	dynlist->nbnode = 0;
	dynlist->nodes  = NULL;
	dynlist->callback.link = NULL;

	/* Setting up type, by default it's POPUP */
	switch(type) {
		case DYNLIST_MENU:
			dynlist->type       = DYNLIST_MENU;
			dynlist->max_len    = MENU_NODE_MAX_LEN;
			dynlist->screen_top = MENU_SCREEN_TOP;
			dynlist->colo_bgd   = MENU_BGD_COLOR;
			dynlist->colo_txt   = MENU_TXT_COLOR;
			dynlist->colo_hov   = MENU_HOV_COLOR;
			dynlist->colo_brd   = MENU_BRD_COLOR;
			dynlist->max_line   = MENU_MAXLN;
			break;

		case DYNLIST_FULL:
			dynlist->type       = DYNLIST_FULL;
			dynlist->max_len    = FULL_NODE_MAX_LEN;
			dynlist->screen_top = FULL_SCREEN_TOP;
			dynlist->colo_bgd   = FULL_BGD_COLOR;
			dynlist->colo_txt   = FULL_TXT_COLOR;
			dynlist->colo_hov   = FULL_HOV_COLOR;
			dynlist->colo_brd   = FULL_BRD_COLOR;
			dynlist->max_line   = FULL_MAXLN;
			break;

		case DYNLIST_ASK:
			dynlist->type       = DYNLIST_ASK;
			dynlist->max_len    = ASK_NODE_MAX_LEN;
			dynlist->screen_top = ASK_SCREEN_TOP;
			dynlist->colo_bgd   = ASK_BGD_COLOR;
			dynlist->colo_txt   = ASK_TXT_COLOR;
			dynlist->colo_hov   = ASK_HOV_COLOR;
			dynlist->colo_brd   = ASK_BRD_COLOR;
			dynlist->max_line   = ASK_MAXLN;
			break;

		case DYNLIST_POPUP:
		default:
			dynlist->type       = DYNLIST_POPUP;
			dynlist->max_len    = POPUP_NODE_MAX_LEN;
			dynlist->screen_top = POPUP_SCREEN_TOP;
			dynlist->colo_bgd   = POPUP_BGD_COLOR;
			dynlist->colo_txt   = POPUP_TXT_COLOR;
			dynlist->colo_hov   = POPUP_HOV_COLOR;
			dynlist->colo_brd   = POPUP_BRD_COLOR;
			dynlist->max_line   = POPUP_MAXLN;
			break;
	}

	return dynlist;
}

/* Libère la mémoire utilisé par une liste */
/* @args : la liste                        */
void DynamicList_Free(dynlist_t *list) {
	dynlist_node_t *node;

	node = list->nodes;

	/* Free all allocated text */
	while(list->nbnode-- > 0) {
		free(node->text);
		node++;
	}

	/* Free allocated node */
	free(list->nodes);
	free(list);
}

/* Libère la mémoire utilisé par un node */
/* @args : le node                       */
void DynamicList_FreeNode(dynlist_node_t *node) {
	if(node->text != NULL)
		free(node->text);

	if(node != NULL)
		free(node);
}