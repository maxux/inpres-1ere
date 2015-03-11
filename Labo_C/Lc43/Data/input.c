#include <stdio.h>
#include <stdlib.h>
#include "__tables.h"
#include "fieldsmanager.h"
#include "datemanager.h"
#include "input.h"
#include "misc.h"
#ifdef WIN32
	#include "Win32Console.h"
#else
	#include "UnixConsole.h"
#endif

/*
   Récupère une chaine de caractère depuis un champ précis
   @args : (pointeur) node, caractères acceptés (define FIELD_ACCEPT_)
*/
void HandleFieldInput_Text(field_node_t *field, char accept) {
	char key;
	unsigned char current = 0;
	char *output;
	char failed = 0;

	output = field->data;
	
	if(output[0] != '\0')
		current = strlen(output);

	while(current != FIELD_EOL) {
		fflush(stdin);
		key = _getch();

		if(failed) {
			Fields_ManageFail(FIELD_FAIL_CLEAR);
			failed = 0;
		}

		/* Working on keycode */
		if(key == KEYCODE_BACKSP) {
			/* Back Space */
			if(current > 0) {
				ClearBackSpace(1);
				current--;
			}
		} else {
			if(key == KEYCODE_ENTER || key == KEYCODE_TAB) {
				output[current] = '\0';

				if(current > 0 && field->valide(output, field->extra_param)) {	/* Test de fonctions pointé */
					current = FIELD_EOL;
				} else {
					Fields_ManageFail(FIELD_FAIL_SHOW);
					failed = 1;
				}
			} else {
				if(current < (signed) field->length - 1) {
					if((accept == FIELD_ACCEPT_ALPHA && __is_alpha(key)) || (accept == FIELD_ACCEPT_ALPHANUM && __is_alpha_num(key)) || (accept == FIELD_ACCEPT_ALPHANUM_EXT && __is_alpha_num_extended(key))) {
						output[current] = key;

						printf("%c", key);
						current++;
					}
				}
			}
		}
	}
}

/*
   Récupère une chaine de caractère formaté pour une date: date_t
   @args : (pointeur) node
*/
void HandleFieldInput_Date(field_node_t *field) {
	char inpdate[] = "  /  /    ";
	char key, failed = 0;
	unsigned char current = 0;
	date_t *output;
	date_t today;

	while(current != FIELD_EOL) {
		fflush(stdin);
		key = _getch();

		if(failed) {
			Fields_ManageFail(FIELD_FAIL_CLEAR);
			failed = 0;
		}

		/* Working on keycode */
		if(key == KEYCODE_BACKSP) {
			/* Back Space */
			if(current > 0) {
				if(current == 3 || current == 6) {	/* One char after '/' */
					ClearBackSpaceDate();
					current--;

				} else ClearBackSpace(1);
				current--;
			}
		} else {
			if(key == KEYCODE_ENTER || key == KEYCODE_TAB) {
				if(current == 10) { /* Date Full */
					output = field->data;
					output->day   = atoi(inpdate);
					output->month = atoi(inpdate+3);
					output->year  = atoi(inpdate+6);

					/* Grabbing current date */
					today = Date_GetToday();

					if(Date_Validate(output->day, output->month, output->year) &&      /* Check date format                        */
					   Date_DateToTimestamp(output) < Date_DateToTimestamp(&today) &&  /* Check date is not in the futur           */
					   output->year <= today.year &&
					   output->year > today.year - MAX_YEAR_OLD                        /* Check MaxYearOld (defined in __tables.h) */
					   ) {
						if(field->valide(output, field->extra_param)) {
							current = FIELD_EOL;
						} else {
							Fields_ManageFail(FIELD_FAIL_SHOW);
							failed = 1;
						}
					} else {
						Fields_ManageFail(FIELD_FAIL_SHOW);
						failed = 1;
					}
				}
			} else {
				if(__is_num(key) && current < 10) {
					inpdate[current] = key;

					printf("%c", key);
					current++;

					if(current == 2 || current == 5) {
						printf("/");
						current++;
					}
				}
			}
		}
	}
}

/*
   Récupère un entier depuis un champ précis
   @args : (pointeur) node, valeur min et max
*/
void HandleFieldInput_Numeric(field_node_t *field, int min, int max) {
	char key, temp[11];
	unsigned char current = 0;
	int *output;
	char failed = 0;

	output = field->data;

	if(*(int*) output > 0) {
		__itoa(*(int*) output, temp);
		current += strlen(temp);
	}

	while(current != FIELD_EOL) {
		fflush(stdin);
		key = _getch();

		if(failed) {
			Fields_ManageFail(FIELD_FAIL_CLEAR);
			failed = 0;
		}

		/* Working on keycode */
		if(key == KEYCODE_BACKSP) {
			/* Back Space */
			if(current > 0) {
				ClearBackSpace(1);
				current--;
			}
		} else {
			if(key == KEYCODE_ENTER || key == KEYCODE_TAB) {
				temp[current] = '\0';

				if(current > 0 && field->valide(temp, field->extra_param)) {
					*output = atoi(temp);

					if(*output >= min && *output <= max) {
						current = FIELD_EOL;
					} else {
						Fields_ManageFail(FIELD_FAIL_SHOW);
						failed = 1;
					}
				} else {
					Fields_ManageFail(FIELD_FAIL_SHOW);
					failed = 1;
				}
			} else {
				if(current < 10) {
					if(__is_num(key)) {
						temp[current] = key;

						printf("%c", key);
						current++;
					}
				}
			}
		}
	}
}

/*
   Récupère un entier depuis un champ précis
   @args : (pointeur) node, valeur min et max
*/
void HandleFieldInput_Float(field_node_t *field, float min, float max) {
	char key, temp[11];
	unsigned char current = 0;
	float *output;
	short failed = 0;
	short dot = 0;

	output = field->data;

	/* if(*(float*) output > 0) {
		// __itoa(*(float*) output, temp);
		current += strlen(temp);
	} */

	while(current != FIELD_EOL) {
		fflush(stdin);
		key = _getch();

		if(failed) {
			Fields_ManageFail(FIELD_FAIL_CLEAR);
			failed = 0;
		}

		/* Working on keycode */
		if(key == KEYCODE_BACKSP) {
			/* Back Space */
			if(current > 0) {
				if(temp[current-1] == '.')
					dot = 0;

				ClearBackSpace(1);
				current--;
			}
		} else {
			if(key == KEYCODE_ENTER || key == KEYCODE_TAB) {
				temp[current] = '\0';

				if(current > 0 && field->valide(temp, field->extra_param)) {
					*output = (float) atof(temp);

					if(*output >= min && *output <= max) {
						current = FIELD_EOL;
					} else {
						Fields_ManageFail(FIELD_FAIL_SHOW);
						failed = 1;
					}
				} else {
					Fields_ManageFail(FIELD_FAIL_SHOW);
					failed = 1;
				}
			} else {
				if(current < 10) {
					if(__is_num(key) || (dot == 0 && current > 0 && (key == ',' || key == '.'))) {
						if(key == ',')
							key = '.';

						if(key == '.')
							dot = 1;

						temp[current] = key;

						printf("%c", key);
						current++;
					}
				}
			}
		}
	}
}

/* From Wikipedia: http://en.wikipedia.org/wiki/Itoa */
/* reverse:  reverse string s in place */
void reverse(char s[]) {
	int i, j;
	char c;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}


/* itoa:  convert n to characters in s */
void __itoa(int n, char s[]) {
	int i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */

	i = 0;
	do {       /* generate digits in reverse order */
		s[i++] = n % 10 + '0';   /* get next digit */

	} while ((n /= 10) > 0);     /* delete it */

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}
