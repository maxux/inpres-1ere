#include <stdio.h>
#include "LC40-Daniel.h"
#include "Win32Console.h"
#include "fieldsmanager.h"
#include "DateCheck.h"

/*
   Récupère une chaine de caractère depuis un champ précis
   @args : (pointeur) node, caractères acceptés (define FIELD_ACCEPT_)
*/
void HandleFieldInput_Text(field_t *field, char accept) {
	char key, current = 0;
	char *output;

	output = field->data;

	while(current != -1) {
		fflush(stdin);
		key = _getch();

		/* Working on keycode */
		if(key == KEYCODE_BACKSP) {
			/* Back Space */
			if(current > 0) {
				ClearBackSpace(1);
				current--;
			}
		} else {
			if(key == KEYCODE_ENTER) {
				if(current > 0) {
					output[current] = '\0';
					current = -1;
				}
			} else {
				if(current < (signed) field->length) {
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
void HandleFieldInput_Date(field_t *field) {
	char inpdate[10] = "  /  /    ";
	char key, current = 0;
	date_t *output;

	while(current != -1) {
		fflush(stdin);
		key = _getch();

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
			if(key == KEYCODE_ENTER) {
				if(current == 10) { /* Date Full */
					output = field->data;
					output->day = atoi(inpdate);
					output->month = atoi(inpdate+3);
					output->year = atoi(inpdate+6);

					if(valide_date(output->day, output->month, output->year)) {
						/* FIXME: Add DATE < TODAY */
						current = -1;

					} else PrintFail();
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
void HandleFieldInput_Numeric(field_t *field, int min, int max) {
	char key, current = 0;
	char temp[10];
	int *output;

	output = field->data;

	while(current != -1) {
		fflush(stdin);
		key = _getch();

		/* Working on keycode */
		if(key == KEYCODE_BACKSP) {
			/* Back Space */
			if(current > 0) {
				ClearBackSpace(1);
				current--;
			}
		} else {
			if(key == KEYCODE_ENTER) {
				if(current > 0) {
					temp[current] = '\0';
					*output = atoi(temp);

					if(*output >= min && *output <= max)
						current = -1;
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
