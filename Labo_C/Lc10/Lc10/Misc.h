/* Define range/no range values */
#define NO_RANGE_VALUE	(short) -1						/* Valeur du NO_RANGE			*/
#define NO_RANGE		(short) NO_RANGE_VALUE, 0, 0	/* Ne pas utiliser de limite	*/
#define USE_RANGE		(short) 0						/* Valeur pour le RANGE			*/

/* Functions Prototypes */
void scanfint(int *to, short range, int min, int max);
void clean_stdin(void);