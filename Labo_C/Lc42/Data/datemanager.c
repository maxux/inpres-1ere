#define _CRT_SECURE_NO_WARNINGS

#include "datemanager.h"

/* Vérifie si une date est valide (année > 0)	*/
/* @args : jour && mois && année				*/
/* Return: 1 si valide, 0 sinon					*/
short Date_Validate(short day, short month, short year) {
	short date_day_by_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	short ret = 0;

	/* Vérification préliminaire */
	if(month > 0 && month < 13 && day > 0 && year > 0) {
		/* Cas spécial pour février	*/
		if(month == 2 && Date_Bissextile(year))
			day--;
		
		/* Vérification de la plage du jour	*/
		if(day <= date_day_by_month[month - 1])
				ret = 1;
	}

	return ret;
}

/* Vérifie si une année est bissextile	*/
/* @args : l'année						*/
/* Return: 1 si bissextile, 0 sinon		*/
short Date_Bissextile(short year) {
	short ret = 0;

	/* Si (divisible par 400) OU (divisible par 4 mais pas par 100)	*/
	if(((year % 100 != 0) && (year % 4) == 0) || (year % 400) == 0)
		ret = 1;

	return ret;
}

/* Renvoi un date_t sur le jour actuel */
/* @args : /                           */
/* Return: date_t sur la date en cours */
date_t Date_GetToday() {
	date_t today;
	time_t timestamp;
	struct tm *timeinfo;

	timestamp = time(NULL);
	timeinfo = localtime(&timestamp);

	today.day   = timeinfo->tm_mday;
	today.month = timeinfo->tm_mon + 1;
	today.year  = timeinfo->tm_year + 1900;

	return today;
}

/* Converti un date_t en time_t (timestamp) */
/* @args : une structure date_t             */
/* Return: un timestamp time_t              */
time_t Date_DateToTimestamp(date_t *mdate) {
	time_t output;
	struct tm *timeinfo;

	output = time(NULL);
	timeinfo = localtime(&output);

	timeinfo->tm_hour = 0;
	timeinfo->tm_min  = 0;
	timeinfo->tm_sec  = 0;
	timeinfo->tm_mday = mdate->day;
	timeinfo->tm_mon  = mdate->month - 1;

	if(mdate->year > 1900)
		timeinfo->tm_year = mdate->year - 1900;

	output = mktime(timeinfo);

	return output;
}