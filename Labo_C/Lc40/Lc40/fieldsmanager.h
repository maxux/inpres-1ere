#include <windows.h>
#include "Win32Console.h"

#define FIELD_BACKGROUND	C_BACK_BLACK
#define FIELD_FOREGROUND	C_FORE_WHITE

#define FIELD_TEXT	   1
#define FIELD_INT	   2
#define FIELD_DATE	   3
#define FIELD_UPPER    4
#define FIELD_TITLE    5
#define FIELD_CODEP	   6
#define FIELD_EOF	   -1

#define FIELD_ACCEPT_ALPHA         1
#define FIELD_ACCEPT_ALPHANUM      2
#define FIELD_ACCEPT_ALPHANUM_EXT  3

#define __FIELD_MAX_ENTRY	32
#define __FIELD_MAX_LENGTH	32

typedef struct {
	/* Nom du champs */
	char name[__FIELD_MAX_LENGTH];

	char type;		 /* Types du champ    */
	size_t length;   /* Longeur du champs */
	COORD start;     /* Position champs   */

	void *data;
	void *index;

} field_t;

/* Prototypes */
short __is_alpha(char chr);
short __is_num(char chr);
short __is_extended(char chr);
short __is_alpha_num(char chr);
short __is_alpha_num_extended(char chr);
void PrintTextField(size_t len);
void PrintDateField();
void Format_Upper(char *str);
void Format_Title(char *str);
void PrintFail();
void HandleField(field_t *field);
void FieldsProcess(field_t *field);