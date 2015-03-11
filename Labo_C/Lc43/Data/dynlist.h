#ifndef __DYNLIST_HEADER
	#define __DYNLIST_HEADER
	#define _CRT_SECURE_NO_WARNINGS

	#ifdef WIN32
		#include "Win32Console.h"
	#else
		#include "UnixConsole.h"
	#endif

	/* Defines */
	#define DYNLIST_DEBUG_ID	-42
	#define DYNLIST_DEBUG_KEY	KEYCODE_F12

	#define DYNLIST_EOL         -2	/* End Of List Process (for callback) */
	#define DYNLIST_POPUP       1
	#define DYNLIST_MENU        2
	#define DYNLIST_FULL        3
	#define DYNLIST_INFO        4
	#define DYNLIST_ASK         5

	#define DYN_TEMP_LEN		128

	#define POPUP_NODE_MAX_LEN	45
	#define POPUP_SCREEN_TOP    5
	#define POPUP_BRD_COLOR     C_FORE_WHITE    /* Defini dans Win32Console.h */
	#define POPUP_TXT_COLOR     C_FORE_WHITE
	#define POPUP_HOV_COLOR     C_FORE_RED    
	#define POPUP_BGD_COLOR     C_BACK_BLUE
	#define POPUP_MAXLN         8

	#define MENU_NODE_MAX_LEN   65
	#define MENU_SCREEN_TOP	    2
	#define MENU_BRD_COLOR      C_FORE_WHITE
	#define MENU_TXT_COLOR      C_FORE_GREY
	#define MENU_HOV_COLOR      C_FORE_GREEN
	#define MENU_BGD_COLOR      C_BACK_BLACK
	#define MENU_MAXLN          15

	#define FULL_NODE_MAX_LEN   TERM_COLS - 4
	#define FULL_SCREEN_TOP     0
	#define FULL_BRD_COLOR      C_FORE_LIGHTBLUE
	#define FULL_TXT_COLOR      C_FORE_DARKGREEN
	#define FULL_HOV_COLOR      C_FORE_WHITE
	#define FULL_BGD_COLOR      C_BACK_BLACK
	#define FULL_MAXLN          21

	#define INFO_NODE_MAX_LEN   50
	#define INFO_SCREEN_TOP     5
	#define INFO_BRD_COLOR      C_FORE_WHITE
	#define INFO_TXT_COLOR      C_FORE_WHITE
	#define INFO_HOV_COLOR      C_BACK_YELLOW
	#define INFO_BGD_COLOR      C_BACK_LIGHTBLUE
	#define INFO_MAXLN          10

	#define ASK_NODE_MAX_LEN   50
	#define ASK_SCREEN_TOP     5
	#define ASK_BRD_COLOR      C_FORE_WHITE
	#define ASK_TXT_COLOR      C_FORE_WHITE
	#define ASK_HOV_COLOR      C_BACK_GREEN
	#define ASK_BGD_COLOR      C_BACK_RED
	#define ASK_MAXLN          5

	#define TOP_BARS	        1
	#define BOT_BARS	        2

	/* Typedef */
	typedef struct {
		int id;              /* id (returned) by node */
		char *text;             /* Dynamic text of node  */

	} dynlist_node_t;

	typedef void (*DYN_CALLBACK)(void *, void *);

	typedef struct {
		void *param;              /* Pointeur vers un paramètre */
		DYN_CALLBACK link;        /* Pointeur vers une fonction de callback */

	} dynlist_callback_t;

	typedef struct {
		size_t nbnode;            /* Number of node      */
		char   type;              /* List Type           */

		short  screen_top;        /* Screen init pos     */
		short  max_len;           /* Length of each line */
		short  max_line;
		unsigned char colo_brd;   /* Couleur des bords   */
		unsigned char colo_txt;   /* Couleur du texte    */
		unsigned char colo_hov;   /* Couleur du choix    */
		unsigned char colo_bgd;   /* Couleur de fond     */

		dynlist_node_t *nodes;          /* Dynamic node list   */
		dynlist_callback_t callback;    /* Function de traite. */

		char debug;               /* Flag to enable debug mode */

	} dynlist_t;

	/* Prototypes */
	dynlist_t * DynamicList_Create(char type);

	dynlist_node_t * DynamicList_Process(dynlist_t *list, dynlist_node_t *result);

	void DynamicList_PopupPrintBorders(dynlist_t *list, char direct);
	void DynamicList_PrintList(dynlist_t *list, dynlist_node_t *node, size_t count, short *col, short *line);
	void DynamicList_PrintWholeZone(dynlist_t *list, dynlist_node_t *node, size_t count, short *col, short *line);
	void DynamicList_MarkCurrentLine(dynlist_t *list, dynlist_node_t *node, short col, short line);
	void DynamicList_UnmarkCurrentLine(dynlist_t *list, dynlist_node_t *node);
	void DynamicList_AppendNode(dynlist_t *list, size_t id, char *text);
	void DynamicList_Info(dynlist_t *list);

	short DynamicList_Ask();

	void DynamicList_FreeNode(dynlist_node_t *node);
	void DynamicList_Free(dynlist_t *list);
#endif
