/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :	Fusée qui vooooolllleeeeeeeee				*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define LINES			13
#define ROWS			11
#define SLEEP_TIME		100
#define TERM_LINES		24
#define TERM_ROWS		80

int main(void) {
	char draw[LINES][ROWS] = {
		"     *     ",
		"    ***    ",
		"  --   --  ",
		" ___   ___ ",
		"____   ____",
		"____   ____",
		"____   ____",
		"____   ____",
		"____   ____",
		"____   ____",
		"  ||   ||  ",
		"   |   |   ",
		"     |     "
	};

	int i, j, k, z = 5;

	while(z > 0) {
		for(k = TERM_LINES; k > 0; k--)
			printf("\n");

		for(i = 0; i < LINES; i++) {
			printf("    ");

			for(j = 0; j < ROWS; j++)
				printf("%c", draw[i][j]);

			printf("\n");
			Sleep(SLEEP_TIME);
		}
		
		for(k = TERM_LINES; k > 0; k--) {
			printf("\n");
			Sleep(SLEEP_TIME);
		}

		z--;
	}

	while(1) {
		for(i = 0; i < TERM_LINES; i++) {
			for(j = 0; j < TERM_ROWS; j++) {
				printf("%c", (j % 2) ? 'O' : ' ');
			}
		}
	}

	return 0;
}