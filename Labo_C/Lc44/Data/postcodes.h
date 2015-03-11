#ifndef __POSTCODES_HEADER
	#define __POSTCODES_HEADER
	#define _CRT_SECURE_NO_WARNINGS

	#include "dynlist.h"

	/* Defines */
	#define POSTCODE_FILENAME	"CodePostaux.txt"

	/* Typedef */
	typedef struct {
		short code;
		size_t addr;

	} zipcode_node_t;

	typedef struct {
		FILE *fp;
		short size;
		zipcode_node_t *list;

	} zipcode_t;

	/* Variable Globale Code Postaux */
	zipcode_t zipc;

	/* Prototypes */
	void TrimName(char *data);
	void ZipCode_BuildIndex(zipcode_t *zip);
	void ZipCode_GetZipName(char *line);
	void ZipCode_GrabName(zipcode_t *zip, size_t addr, char *buffer , size_t len);
	dynlist_node_t * ZipCode_GetListFromCode(zipcode_t *zip, short code);
	void ZipCode_Init(zipcode_t *zip);
	void ZipCode_Close(zipcode_t *zip);

#endif