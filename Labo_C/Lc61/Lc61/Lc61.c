#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Lc61.h"

/* Affiche la liste du chainage */
/* @args: le pointeur vers le pointeur de tête de fiche num/alpha, l'ordre a afficher (define FOLLOW_) */
void Affichage(fiche_t **start, char ptnext) {
	fiche_t *show;

	if(*start != NULL) {
		show = *start;

		while(show != NULL) {
			printf(" > %s - %d ans.\n", show->nom, show->age);

			if(ptnext == FOLLOW_BY_NUM)
				show = show->num_next;
			else
				show = show->alpha_next;
		}

	} else printf("Access denied: list empty\n");
}

/* Insert une fiche dans le chainage, trié par ordre alphabétique */
/* @args: le pointeur vers le pointeur de tête de liste alpha et numerique, un pointeur vers la nouvelle fiche */
void Insertion(fiche_t **start_alpha, fiche_t **start_num, fiche_t *fiche) {
	fiche_t *prev, *show;

	printf("Inserting... ");

	if(*start_alpha != NULL) {
		/* Alpha Part */
		show = *start_alpha;
		prev = NULL;

		while(show != NULL && strcmp(fiche->nom, show->nom) > 0) {
			prev = show;
			show = show->alpha_next;
		}

		if(prev == NULL) {
			fiche->alpha_next = *start_alpha;
			*start_alpha = fiche;

		} else {
			fiche->alpha_next = prev->alpha_next;
			prev->alpha_next = fiche;
		}

		/* Numeric Part */
		show = *start_num;
		prev = NULL;

		while(show != NULL && fiche->age > show->age) {
			prev = show;
			show = show->num_next;
		}

		if(prev == NULL) {
			fiche->num_next = *start_num;
			*start_num = fiche;

		} else {
			fiche->num_next = prev->num_next;
			prev->num_next = fiche;
		}
			

	} else {
		*start_num   = fiche;
		*start_alpha = fiche;
	}

	printf("ok.\n");
}

/* Encode une fiche créée dynamiquement */
/* @args: le pointeur vers le pointeur de tête de liste alpha et numérique */
void Encodage(fiche_t **start_alpha, fiche_t **start_num) {
	fiche_t *fiche;
	char temp[4];
	size_t len;

	fiche = (fiche_t*) malloc(sizeof(fiche_t));
	if(fiche == NULL)
		exit(1);

	fiche->nom[0]     = '\n';
	fiche->num_next   = NULL;
	fiche->alpha_next = NULL;

	/* Encodage nom */
	do {
		printf("Nom: ");

		fflush(stdin);
		fgets(fiche->nom, sizeof(fiche->nom), stdin);

	} while(fiche->nom[0] == '\n');

	/* Strip \n */
	len = strlen(fiche->nom);
	fiche->nom[len - 1] = '\0';
	
	/* Encodage Age */
	do {
		printf("Age: ");

		fflush(stdin);
		fgets(temp, sizeof(temp), stdin);

	} while((fiche->age = atoi(temp)) == 0);
	
	/* Insert l'élement dans la liste */
	Insertion(start_alpha, start_num, fiche);
}

/* Free tout les malloc de la liste */
/* @args: le pointeur vers le pointeur de tête de fiche (alpha ou num sans importance) */
void CleanList(fiche_t **start) {
	fiche_t *now, *next = NULL;

	now = *start;

	if(now != NULL && now->num_next != NULL)
		next = now->num_next;

	while(now != NULL) {
		free(now);

		if(next != NULL) {
			now = next;
			next = now->num_next;

		} else now = NULL;
	}
}

int main(void) {
	fiche_t *list1 = NULL, *list2 = NULL, **start_alpha, **start_num;
	char key, quit = 0;

	start_alpha = &list1;
	start_num   = &list2;

	printf("1 - Encodage\n");
	printf("2 - Affichage (ordre numerique)\n");
	printf("3 - Affichage (ordre alphabetique)\n");
	printf("4 - Quitter\n\n");

	printf("root ~ # ");

	while(!quit) {
		key = _getch();

		switch(key) {
			case '1':
				printf("PUSH fiche_t\n\n");
				Encodage(start_alpha, start_num);
				printf("\nroot ~ # ");
				break;

			case '2':
				printf("DSPL PTR ADDR 0x%p -> 0x%p\n\n", start_num, *start_num);
				Affichage(start_num, FOLLOW_BY_NUM);
				printf("\nroot ~ # ");
				break;
			
			case '3':
				printf("DSPL PTR ADDR 0x%p -> 0x%p\n\n", start_alpha, *start_alpha);
				Affichage(start_alpha, FOLLOW_BY_ALPHA);
				printf("\nroot ~ # ");
				break;

			case '4':
				printf("FLUSH MEMORY && QUIT\n\n");
				quit = 1;
				break;
		}
	}

	CleanList(start_num);

	return 0;
}