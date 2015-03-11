/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   : Prix dégressant								*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float op1, op2;
	char *operation;

	operation = (char*) malloc(sizeof(char*)); /* char* else fail on free */
	printf("Op 1: ");
	fflush(stdin);
	scanf("%d", &op1);

	printf("Op 2: ");
	fflush(stdin);
	scanf("%d", &op2);

	printf("Operation (+, -, *, /, ^, R): ");
	fflush(stdin);
	fgets(operation, 2, stdin);

	switch(operation[0]) {
		case 43: /* ASCII + */
			printf("ITS A PLUS\n");
			break;

		default:
			printf("Donno\n");
	}

	fflush(stdin);
	getchar();

	return 0;
}