/********************************************************/
/* Nom    : DANIEL Maxime								*/
/* Groupe : 2125										*/
/* Contact: maxux.unix@gmail.com						*/
/* File   :					*/
/********************************************************/

/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_LINES	5
#define MAX_COLS	10

void DisplayGrind(char *table, short lines, short cols) {
	short i, j;

	/* Cols ID */
	printf("   | ");

	for(i = 0; i < cols; i++)
		printf("%2d ", i);

	printf("\n---+");

	/* Cols border */
	for(i = 0; i < cols; i++)
		printf("---");

	printf("\n");

	/* Lines ID */
	for(i = 0; i < lines; i++) {
		printf("%2d | ", i);

		/* Print Values */
		for(j = 0; j < cols; j++) {
			printf("%2d ", *table);
			table++;
		}

		printf("\n");
	}
}

void GetCoord(char *start, char *position, short lines, short cols, short *x, short *y) {
	*x = (position - start) % cols;
	*y = (position - start) / cols;
}

short SetRange(char *tbl, char *center, short lines, short cols, char **min, char **max) {
	short cur_line, cur_pos;

	if(center < tbl || center > tbl + (cols * lines)) {
		/* printf("%p: Out of table (%p - %p)\n", center, tbl, center); */
		return 0;
	}

	cur_pos  = (center - tbl) % cols;
	cur_line = (center - tbl) / cols;

	if(cur_pos >= 0 && cur_pos <= cols - 1) {
		*min = tbl + (cur_line * cols);
		*max = *min + cols;

	} else return 0;

	return 1;
}

char * CheckAround(char *tbl, char *center, short lines, short cols, char **better) {
	short i, j;
	char *min_addr = NULL, *max_addr = NULL, *this_max;
	char *pnt;

	this_max = center;

	/* printf("DEB: %p - CUR: %p\n", tbl, center);
	printf("POS: %d, %d\n", pos_line, cur_line); */

	for(i = -1; i < 2; i++) {		/* Check Methode: Lines -1, 0, 1 */
		/* printf("New Center: %p\n", center + (i * cols)); */

		if(SetRange(tbl, center + (i * cols), lines, cols, &min_addr, &max_addr) == 0) {
			/* printf("Skip... %p\n", center + (i * cols)); */
			continue;

		} else pnt = (center + (i * cols)) - 1;

		/* printf("RANGE: %p - %p (%p - %p) -- Testing: %p\n", min_addr, max_addr, tbl, tbl + (cols * lines), pnt); */

		for(j = 0; j < 3; j++) {
			if(pnt < min_addr || pnt > max_addr) {
				/* printf("%p: Out Of Range\n", pnt); */

			} else {				
				if(*pnt > *this_max) {
					this_max = pnt;
					/* printf("-- YES --\n"); */
				}
			}

			pnt++;
		}
	}

	/* printf("Return... %p - %p: %d\n", this_max, center, *this_max); */
	
	*better = this_max;

	if(this_max == center)
		return NULL;

	else return this_max;
}

void FindBetterZone(char *table, short lines, short cols, short *x, short *y) {
	char *better, *ntable;

	ntable = table;
	while((ntable = CheckAround(table, ntable, lines, cols, &better)) != NULL) {}

	GetCoord(table, better, lines, cols, x, y);
}

int main(void) {
	short x, y;
	char table[MAX_LINES][MAX_COLS] =
		{{2, 8, 4, 3, 7, 5, 8, 9, 3, 10},
		 {9, 4, 5, 7, 12, 5, 6, 7, 10, 2},
		 {10, 5, 15, 1, 5, 9, 10, 2, 5, 7},
		 {10, 5, 7, 8, 9, 10, 4, 2, 5, 8},
		 {9, 5, 4, 7, 8, 6, 3, 2, 10, 11}};

	DisplayGrind(&table[0][0], MAX_LINES, MAX_COLS);
	FindBetterZone(&table[0][0], MAX_LINES, MAX_COLS, &x, &y);

	printf("\nZone: %hd, %hd\n", x, y);

	fflush(stdin);
	getchar();
	
	return 0;
}