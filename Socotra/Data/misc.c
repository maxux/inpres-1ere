#define _CRT_SECURE_NO_WARNINGS

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include "Win32Console.h"

#ifdef WIN32
	#include <windows.h>
#endif

/* Quitte le programme avec un message d'erreur */
void Exit_Fail() {
	printf("\nAn error occured. Exiting...\n");

	#ifdef WIN32
		_fcloseall();
	#else
		fcloseall();
	#endif

	getchar();
	exit(2);
}

/* Affiche une erreur de traitement de fichier (avec la raison) puis quitte */
/* args: le nom du fichier qui a provoqué l'erreur */
void File_Fail(char *filename) {
	ClearScreen();
	perror(filename);
	Exit_Fail();
}
