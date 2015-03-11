#ifndef __FIELDSMAN_HEADER
	#define __FIELDSMAN_HEADER
	#ifdef WIN32
		#include "Win32Console.h"
	#else
		#include "UnixConsole.h"
	#endif

	#define FIELD_BACKGROUND	C_BACK_BLACK
	#define FIELD_FOREGROUND	C_FORE_WHITE

	#define FIELD_TEXT	   1
	#define FIELD_INT	   2
	#define FIELD_DATE	   3
	#define FIELD_UPPER    4
	#define FIELD_TITLE    5
	#define FIELD_CODEP	   6

	#define FIELD_ACCEPT_ALPHA         1
	#define FIELD_ACCEPT_ALPHANUM      2
	#define FIELD_ACCEPT_ALPHANUM_EXT  3

	#define __FIELD_MAX_ENTRY	32
	#define __FIELD_MAX_LENGTH	32

	#define FIELD_FAIL_SHOW     1
	#define FIELD_FAIL_CLEAR    2

	#define FIELD_RESTRICT_ALLOW	1
	#define FIELD_RESTRICT_DENIED	0

	#define FIELD_EOL     255

	typedef struct {
		/* Nom du champs */
		char *name;

		char type;		 /* Types du champ    */
		size_t length;   /* Longeur du champs */
		COORD start;     /* Position champs   */

		void *data;
		void *index;

		short editable;

	} field_node_t;

	typedef struct {
		short nbnodes;
		field_node_t *nodes;

	} field_t;

	/* Prototypes */
	/* Char Detection */
	short __is_alpha(char chr);
	short __is_num(char chr);
	short __is_extended(char chr);
	short __is_alpha_num(char chr);
	short __is_alpha_num_extended(char chr);

	/* Priting */
	void PrintTextField(char *data, size_t len);
	void PrintDateField(date_t *date);
	void Fields_ManageFail(char type);

	/* Convertions */
	void Format_Upper(char *str);
	void Format_Title(char *str);

	/* Handling */
	void Fields_HandleField(field_node_t *field);
	void Fields_Process(field_t *fields);
	void Fields_AppendNode(field_t *field, char name[], void *pointer, size_t length, char type, short editable);

	/* Creating */
	field_t * Fields_Create();
	void Fields_Free(field_t *field);
#endif
