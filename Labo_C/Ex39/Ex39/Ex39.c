/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :												*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/* kg/m³ */
#define MASS_ACIER	7800
#define MASS_BETON	1250
#define MASS_CHENE	850

#define TYPE_RECT	1
#define TYPE_TRAP	2
#define TYPE_DT		3
#define SHAPE_MAX	3

#define TYPE_ACIER	1
#define TYPE_BETON	2
#define TYPE_CHENE	3
#define MAT_MAX		3

#define DEFAULT_LENGTH	5

void scanfint(int *to) {
	char ok = 0;
	int ret;

	while(!ok) {
		fflush(stdin);
		ret = scanf("%d", to);
		
		if(ret > 0)
			ok = 1;

		if(*to < 1)
			*to = -*to;
	}
}

int main(void) {
	int type, dimension[4];
	double volume;

	printf("Entrez le type de poutre:\n");
	printf("%d) Rectangle\n",	TYPE_RECT);
	printf("%d) Trapeze\n",		TYPE_TRAP);
	printf("%d) En double T\n",	TYPE_DT);

	type = -1;

	do {
		fflush(stdin);
		printf("# ");
		scanf("%d", &type);

	} while(type < 0 || type > SHAPE_MAX);

	switch(type) {
		case TYPE_RECT:
			printf("\nLongueur [m]: ");
			scanfint(&dimension[0]);

			printf("Largeur [m]: ");
			scanfint(&dimension[1]);

			volume = (dimension[0] * dimension[1]) * DEFAULT_LENGTH;
			printf("Volume: %.2lf m3\n\n", volume);
			break;

		case TYPE_TRAP:
			printf("\nGd Base: ");
			scanfint(&dimension[0]);

			printf("Pt Base: ");
			scanfint(&dimension[1]);

			printf("Hauteur: ");
			scanfint(&dimension[2]);

			volume = ((dimension[0] + dimension[1]) * ((float) dimension[2] / 2)) * DEFAULT_LENGTH;
			printf("Volume: %.2lf m3\n\n", volume);
			break;

		case TYPE_DT:
			printf("\nGd Longueur: ");
			scanfint(&dimension[0]);

			printf("Gd Largeur: ");
			scanfint(&dimension[1]);

			printf("\nPt Longueur: ");
			scanfint(&dimension[2]);

			printf("Pt Largeur: ");
			scanfint(&dimension[3]);

			volume = ((dimension[0] * dimension[1]) - ((dimension[2] * dimension[3]) * 2)) * DEFAULT_LENGTH;
			printf("Volume: %.2lf m3\n\n", volume);
			break;

		default:
			printf("Oh, there is a bug !\n");
			return 1;
	}

	printf("Entrez le type de materiau:\n");
	printf("%d) Acier\n",		TYPE_ACIER);
	printf("%d) Beton arme\n",	TYPE_BETON);
	printf("%d) Chene\n",		TYPE_CHENE);

	type = -1;

	do {
		fflush(stdin);
		printf("# ");
		scanf("%d", &type);

	} while(type < 0 || type > MAT_MAX);

	switch(type) {
		case TYPE_ACIER:
			printf("\nMasse volumique: %.3lf T\n", (volume * MASS_ACIER) / 1000);
			break;

		case TYPE_BETON:
			printf("\nMasse volumique: %.3lf T\n", (volume * MASS_BETON) / 1000);
			break;

		case TYPE_CHENE:
			printf("\nMasse volumique: %.3lf T\n", (volume * MASS_CHENE) / 1000);
			break;

		default:
			printf("Oh, there is a bug !\n");
			return 1;
	}


	fflush(stdin);
	getchar();

	return 0;
}