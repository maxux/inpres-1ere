#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	int a, b;
	float moy;

	printf("Veuillez saisir un entier: ");

	fflush(stdin);
	scanf("%d", &a);

	printf("Veuillez en saisir un deuxieme: ");

	fflush(stdin);
	scanf("%d", &b);

	moy = (float)(a + b) / 2;
	printf("\nLa moyenne entre %d et %d est: %.2f\n", a, b, moy);
	
	fflush(stdin);
	getchar();

	return 0;
}