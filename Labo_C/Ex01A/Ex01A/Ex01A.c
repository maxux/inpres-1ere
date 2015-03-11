#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	int a, b;

	printf("Veuillez saisir un entier: ");

	fflush(stdin);
	scanf("%d", &a);

	printf("Veuillez en saisir un deuxieme: ");

	fflush(stdin);
	scanf("%d", &b);

	printf("\nLa somme de %d et %d est: %d\n", a, b, a + b);
	
	fflush(stdin);
	getchar();

	return 0;
}