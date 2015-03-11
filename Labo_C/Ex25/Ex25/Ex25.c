/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Calcul d'un salaire horaire					*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int heure;
	float salhor, hebdo;

	printf("Saisir le salaire horaire: ");

	fflush(stdin);
	scanf("%f", &salhor);

	printf("Saisir le nombre d'heures: ");
	fflush(stdin);

	scanf("%d", &heure);

	if(heure < 38)
		hebdo = heure * salhor;
	else
		hebdo = (((heure / 38) * 38) * salhor) + ((heure % 38) * (salhor * (float) 1.25));
	
	printf("\nSalaire Hebdomadaire: %.1f\n", hebdo);

	fflush(stdin);
	getchar();
	
	return 0;
}