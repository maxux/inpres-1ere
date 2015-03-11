#ifndef __DATEMANAGER_HEADER
	#define __DYNLIST_HEADER
	#include "__tables.h"
	#include <time.h>

	short Date_Validate(short day, short month, short year);
	short Date_Bissextile(short year);
	date_t Date_GetToday();
	time_t Date_DateToTimestamp(date_t *mdate);
#endif