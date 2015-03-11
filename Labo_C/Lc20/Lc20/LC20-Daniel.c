/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :	LC20 - Travail sur un tableau à 2 dim.		*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include "LC20-Daniel.h"
#include "Display.h"
#include "DateOrder.h"
#include "Input.h"

#include <stdio.h>

int main(void) {
	short dates[MAX_DATE][3];	/* Tableau de date									*/
	short tsize, i;				/* tsize contiendra le nombre de LIGNES du tableau	*/
	short *pdate;				/* Pointeur vers les dates							*/

	/* Récupère le nombre de dates à entrer */
	printf("Entrez le nombre de dates: ");
	scanfshort(&tsize, 0, MAX_DATE);

	/* Encode chaque date */
	pdate = &dates[0][0];
	for(i = 0; i < tsize; i++, pdate += 3) {
		printf("Entrez la date numero %hd: ", i + 1);
		encode_date(pdate);
	}

	printf("\n");

	/* Affichage du tableau avant le tri	*/
	printf("Avant le tri:\n");

	pdate = &dates[0][0];
	display_date(pdate, tsize);

	/* Tri des dates */
	pdate = &dates[0][0];
	order_date_all(pdate, tsize);

	/* Affichage du tableau après le tri	*/
	printf("\nApres le tri:\n");

	pdate = &dates[0][0];
	display_date(pdate, tsize);

	/* Attente de la pression d'une touche	*/
	fflush(stdin);
	getchar();

	return 0;
}