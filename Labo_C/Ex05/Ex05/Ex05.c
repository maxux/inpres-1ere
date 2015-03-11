/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Convertisseur °C -> °F						*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

float degtofar(float celc) {
	return (float)(1.8 * celc) + 32;
}

int main(void) {
	float deg, trans;

	printf("Temperature en degres Celcius: ");

	fflush(stdin);
	scanf("%f", &deg);

	trans = degtofar(deg);

	printf("\n%f degres Celcius => %f degres Fareinth\n", deg, trans);
	
	/* End Of Code */
	fflush(stdin);
	getchar();

	return 0;
}