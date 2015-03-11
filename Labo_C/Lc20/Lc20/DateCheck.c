#include "DateCheck.h"

/* Vérifie si une date est valide (année > 0)	*/
/* @args : jour && mois && année				*/
/* Return: 1 si valide, 0 sinon					*/
short valide_date(short day, short month, short year) {
	short date_day_by_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	short ret = 0;

	/* Vérification préliminaire */
	if(month > 0 && month < 13 && day > 0 && year > 0) {
		/* Cas spécial pour février	*/
		if(month == 2 && is_bissextile(year))
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
short is_bissextile(short year) {
	short ret = 0;

	/* Si (divisible par 400) OU (divisible par 4 mais pas par 100)	*/
	if(((year % 400) == 0) || ((year % 100 != 0) && (year % 4) == 0))
		ret = 1;

	return ret;
}