#include <stdio.h>
#include <stdlib.h>
#include "misc.h"

/* Quitte le programme avec un message d'erreur */
void Exit_Fail() {
	printf("\n -- OPERATION FAILED. Exiting...\n");
	exit(2);
}