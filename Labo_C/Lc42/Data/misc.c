#define _CRT_SECURE_NO_WARNINGS

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"

#ifdef WIN32
	#include <windows.h>
#endif

/* Quitte le programme avec un message d'erreur */
void Exit_Fail() {
	printf("-> FAILED. Exiting...\n");

	#ifdef WIN32
		_fcloseall();
	#else
		fcloseall();
	#endif

	getchar();
	exit(2);
}

void File_Fail(char *filename) {
	printf("-> Error handling file <%s>.\n", filename);
	Exit_Fail();
}
