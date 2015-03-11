/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "DateCheck.h"

/* Encode une date (format DD-MM-YY)				*/
/* @args: un pointeur vers le début d'un vecteur	*/
void encode_date(short *date) {
	int ret = 0;
	short ok = 0;

	while(!ok) {
		fflush(stdin);
		printf(" (D-M-Y) # ");

		ret = scanf("%hd-%hd-%hd", date, (date + 1), (date + 2));

		/* Si on a bien mis les 3 arguments et que la date est valide */
		if(ret == 3 && valide_date(*date, *(date + 1), *(date + 2))) {
			ok = 1;

		} else printf("Date invalide. ");
	}
}

/* Encode un short dans un pointeur avec test de validité	*/
/* @args: pointeur vers un short && min && max				*/
/*        si min > max, les limites sont ignorées			*/
void scanfshort(short *to, short min, short max) {
	int ret = 0;
	short ok = 0;

	while(!ok) {
		fflush(stdin);
		printf("# ");

		ret = scanf("%hd", to);

		if(ret > 0) {
			if(min <= max) {	/* Use Limits */
				if(*to > min && *to < max)
					ok = 1;

			} else ok = 1;
		}
	}
}