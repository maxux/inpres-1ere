/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Input.h"

int trim_lf(char *string, short maxlen) {
	short i = 0;

	while(i < maxlen) {
		if(*string == '\n') {
			*string = '\0';
			return 0;
		}

		i++;
		string++;
	}
	
	return 1;
}

/* Récupère de manière sécurisé, une chaine depuis le clavier
   @args: pointeur vers la chaine
*/
void scanfword(char *to, short maxlen) {
	char *rcode;

	rcode = NULL;
	while(rcode == NULL) {
		printf("# ");

		fflush(stdin);
		rcode = fgets(to, maxlen, stdin);
		trim_lf(to, maxlen);
	}
}

/* Récupère de manière sécurisé, un short positif depuis le clavier
   @args: pointeur vers la variable, la valeur maximal que l'utilisateur peut entrer
*/
void scanfshort(short *to, short max) {
	char ok = 0;
	int ret;

	while(!ok) {
		fflush(stdin);
		printf("# ");

		ret = scanf("%hd", to);
		
		if(ret > 0 && *to > 0)
			if(max == 0 || *to <= max)
				ok = 1;
	}
}