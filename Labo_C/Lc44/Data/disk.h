#ifndef __DISK_HEADER
	#include "index.h"
	#define __DISK_HEADER
	#define _CRT_SECURE_NO_WARNINGS

	#define DEFAULT_FILENAME        "default"

	short Files_Init_Check(char *findex, char *fouvrier, char *fchantier, char *foccupe, index_t *index);
#endif