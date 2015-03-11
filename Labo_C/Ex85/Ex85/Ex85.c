/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :					*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

void scanfword(char *to) {
	char ok = 0;
	int ret;

	while(!ok) {
		fflush(stdin);
		printf("# ");

		ret = scanf("%s", to);
		
		if(ret > 0 && *to > 0)
			ok = 1;
	}
}

short nboccur(char *chaine, char *str) {
	short occur = 0;
	char *pt;

	pt = chaine;
	
	while((pt = strstr(pt, str)) != NULL) {
		occur++;
		pt += strlen(str);
	}

	return occur;
}

int main(void) {
	char chaine[32], str[32];

	printf("Entrez une chaine: ");
	scanfword(&chaine[0]);

	printf("Entrez une occurence: ");
	scanfword(&str[0]);

	printf("Occurences: %d\n", nboccur(&chaine[0], &str[0]));

	fflush(stdin);
	getchar();

	return 0;
}