/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Map Printer									*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int yval(int y) {
	if(y < 0)
		return 0;

	if(y == 0)
		return 1;

	if(y > 0)
		return 2;
	
	return -1;
}

void coor(int val) {
	printf("Votre point se trouve en: %d\n", val);
}

int main(void) {
	int x, y;

	printf("Entrez X: ");
	fflush(stdin);
	scanf("%d", &x);

	printf("Entrez Y: ");
	fflush(stdin);
	scanf("%d", &y);

	if(x < 0) {
		switch(yval(y)) {
			case 0: coor(7);	break;
			case 1: coor(4);	break;
			case 2: coor(1);	break;
		}

	} else if(x == 0) {
		switch(yval(y)) {
			case 0: coor(2);	break;
			case 1: coor(5);	break;
			case 2: coor(8);	break;
		}

	} else if(x > 0) {
		switch(yval(y)) {
			case 0: coor(9);	break;
			case 1: coor(6);	break;
			case 2: coor(3);	break;
		}
	}

	fflush(stdin);
	getchar();

	return 0;
}