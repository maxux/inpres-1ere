/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Calcul d'une vitesse moyenne				*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int h, m;
	float dist, moy;

	printf("Saisissez une distance en km: ");

	fflush(stdin);
	scanf("%f", &dist);

	printf("Saisissez une duree [hh:mm]: ");

	fflush(stdin);
	scanf("%d:%d", &h, &m);

	/* Calcul */
	moy = dist / (h + ((float) m / 60));

	printf("\nVitesse moyenne: %.2f km/h\n", moy);

	fflush(stdin);
	getchar();

	return 0;
}