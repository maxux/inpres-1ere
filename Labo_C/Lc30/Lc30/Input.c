/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Input.h"

/* Récupère de manière pseudo-sécurisé, une chaine depuis le clavier
   @args: pointeur vers la chaine
*/
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

/* Encodage de noms dans un tableau à deux dimensions, et écrit l'index en temps-réel
   @args: pointeur vers le début du tableau, pointeur vers le début du vecteur d'index, le nombre de ligne, la taille d'une ligne
*/
void EncodeNamesIndex(char *table, char **index, short nblines, short max_length) {
	short i;

	for(i = 0; i < nblines; i++) {
		/* Writing Index */
		*index = table;

		/* Writing DATA */
		printf("Entrez le nom [%d]: ", i + 1);
		scanfword(table);

		table += max_length;
		index++;
	}

	*index = NULL;
}