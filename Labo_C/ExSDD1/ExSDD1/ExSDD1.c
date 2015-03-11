#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "ExSDD1.h"

void FollowStack(pile_t **start) {
	pile_t *next;

	if(*start != NULL) {
		next = 
		while(*start != NULL)
	} else printf("Pile vide\n");
}

int main(void) {
	pile_t *pile = NULL, **start;
	char key;

	start = &pile;

	printf("1 - push\n");
	printf("2 - pop\n");
	printf("3 - gdb\n");
	printf("4 - return 0;\n");

	while((key = _getch()) != '4') {
		switch(key) {
			case '1':
				
				break;

			case '2':

				break;

			case '3':
				FollowStack(start);
				break;
		}
	}

	return 0;
}