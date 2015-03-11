#include "DateOrder.h"

/*
	 -- Pour chaque colonne (jour, mois, année), on défini une target qui commence toujours à l'élément 0 de la ligne
	    (exemple, pour trier par mois la ligne "2/4/2001", la target pointe sur 2.
		La fonction order_date décalle elle même la target en fonction du tri demandé.

	 -- La fonction compare chaque fois la valeur de la colonne en fonction du décalage du tri
	    une fois la bonne ligne trouvée, on positionne APRES la ligne existante (dans le cas ou la valeur précédente est égale)
		la nouvelle ligne.

	Grace à la fonction affect_x_data, on a un gain de ligne dans order_date (pour affecte a chaque fois les 3 valeurs),
	quelque soit la colonne qu'on traite (grace au décallage avec order_by)
*/

/* Copie une partie d'un vecteur/tableau dans un autre	*/
/* @args: un pointeur vers un vecteur destination && pointeur vecteur source && nbr case à copier	*/
void affect_x_data(short *pdest, short *psource, short count) {
	short i;

	for(i = 0; i < count; i++)				/* Pour chaque element					*/
		*(pdest + i) = *(psource + i);		/* Affecter la source à la destination	*/
}

/* Trie par insertion un tableau, avec plusieurs colonne */
/* @args: un pointeur vers le début du tableau de date && la taille du tableau (nbr ligne)
          un pointeur vers le début de la ligne qui sert de cible &&
		  une valeur de décallage à utiliser avec les define ORDER_BY_						*/
void order_date(short *date, short tsize, short *targ, short order_by) {		/* Par insertion */
	short i, *read, *write, ctarg[3], *target;

	target  = ctarg;						/* Pointeur vers targ. Target est un pointeur vers une COPIE de la cible.	*/
	affect_x_data(target, targ, 3);			/* On affecte dans le vecteur temporaire, une copie de la cible				*/
	
	read  = (date + ((tsize - 1) * 3));
	write = read + 3;

	i = tsize + 1;
	while(i > 0 && *(target + order_by) < *(read + order_by)) {
		affect_x_data(write, read, 3);
		
		read -= 3;				/* On passe à l'élement suivant	*/
		write -= 3;

		i--;
	}

	affect_x_data(write, target, 3);				/* On affecte les 3 element du tableau	*/
}

/* Trie le tableau pour une colonne précise																					*/
/* @args: pointeur vers le début du tableau de date && la taille du tableau (nbr ligne) && la colonne à trier (voir define)	*/
void order_date_by(short *date, short tsize, short order_by) {
	short i, *value;

	value = date+3;
	for(i = 1; i < tsize; i++, value += 3)
		order_date(date, i, value, order_by);
}

/* Trie l'ingégralité du tableau (jour, mois puis année)								*/
/* @args: pointeur vers le début du tableau de date && la taille du tableau (nbr ligne)	*/
void order_date_all(short *date, short tsize) {
	order_date_by(date, tsize, ORDER_BY_DAY);
	order_date_by(date, tsize, ORDER_BY_MONTH);
	order_date_by(date, tsize, ORDER_BY_YEAR);
}