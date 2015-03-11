#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Lc62.h"

/* Affiche la liste du chainage */
/* @args: le pointeur vers le pointeur de tête de fiche */
void Affichage(fiche_t **start) {
	fiche_t *show;

	if(*start != NULL) {
		show = *start;

		while(show != NULL) {
			printf(" > %s - %d ans.\n>> Next: 0x%x\n\n", show->nom, show->age, show->next);
			show = show->next;
		}

	} else printf("Access denied: list empty\n");
}

/* Insert une fiche dans le chainage, trié par ordre alphabétique */
/* @args: le pointeur vers le pointeur de tête de liste, un pointeur vers la nouvelle fiche */
void Insertion(fiche_t **start, fiche_t *fiche) {
	fiche_t *prev, *show;

	printf("Inserting... ");

	if(*start != NULL) {
		show = *start;
		prev = NULL;

		while(show != NULL && strcmp(fiche->nom, show->nom) > 0) {
			prev = show;
			show = show->next;
		}

		if(prev == NULL) {
			fiche->next = *start;
			*start = fiche;

		} else {
			fiche->next = prev->next;
			prev->next = fiche;
		}
			

	} else *start = fiche;

	printf("ok.\n");
}

/* Encode une fiche créée dynamiquement */
/* @args: le pointeur vers le pointeur de tête de liste */
void Encodage(fiche_t **start) {
	fiche_t *fiche;
	char temp[4], nom_temp[128];
	size_t len;

	fiche = (fiche_t*) malloc(sizeof(fiche_t));
	if(fiche == NULL)
		exit(1);

	nom_temp[0] = '\n';
	fiche->next = NULL;

	/* Encodage nom */
	do {
		printf("Nom: ");

		fflush(stdin);
		fgets(nom_temp, sizeof(nom_temp), stdin);

	} while(nom_temp[0] == '\n');

	/* Strip \n */
	len = strlen(nom_temp);
	nom_temp[len - 1] = '\0';

	fiche->nom = (char *) malloc(sizeof(char) * len);
	strcpy(fiche->nom, nom_temp);
	
	/* Encodage Age */
	do {
		printf("Age: ");

		fflush(stdin);
		fgets(temp, sizeof(temp), stdin);

	} while((fiche->age = atoi(temp)) == 0);
	
	/* Insert l'élement dans la liste */
	Insertion(start, fiche);
}

/* Free tout les malloc de la liste */
/* @args: le pointeur vers le pointeur de tête de fiche */
void CleanList(fiche_t **start) {
	fiche_t *now, *next = NULL;

	now = *start;

	if(now != NULL && now->next != NULL)
		next = now->next;

	while(now != NULL) {
		free(now->nom);
		free(now);

		if(next != NULL) {
			now = next;
			next = now->next;

		} else now = NULL;
	}
}

int main(void) {
	fiche_t *list = NULL, **start;
	char key, quit = 0;

	start = &list;

	printf("1 - Encodage\n");
	printf("2 - Affichage\n");
	printf("3 - Quitter\n\n");

	printf("root ~ # ");

	while(!quit) {
		key = _getch();

		switch(key) {
			case '1':
				printf("PUSH fiche_t\n\n");
				Encodage(start);
				printf("\nroot ~ # ");
				break;

			case '2':
				printf("DSPL PTR ADDR 0x%p -> 0x%p\n\n", start, *start);
				Affichage(start);
				printf("\nroot ~ # ");
				break;

			case '3':
				printf("FLUSH MEMORY && QUIT\n\n");
				quit = 1;
				break;
		}
	}

	CleanList(start);

	return 0;
}