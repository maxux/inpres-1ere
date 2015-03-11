/* VC++ 2008 scanf Warning Fix */
#define _CRT_SECURE_NO_WARNINGS

#include "Misc.h"
#include <stdio.h>

/* Récupère de manière blindé, un int depuis l'stdin											*/
/* @args: pointeur vers une récupération && USE_RANGE ou NO_RANGE && valeur min && valeur max	*/
void scanfint(int *to, short range, int min, int max) {
	int ret = 0;
	short ok = 0;

	while(!ok) {
		fflush(stdin);
		printf("# ");

		ret = scanf("%d", to);
		if(ret > 0)
			if(range == NO_RANGE_VALUE || (*to > min && *to < max))
				ok = 1;
	}
}
