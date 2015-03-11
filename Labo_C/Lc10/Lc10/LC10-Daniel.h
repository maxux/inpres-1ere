/* Project Settings */
#define VECT_SIZE			128		/* Taille maximal du vecteur (de base)	*/
#define VECT_MAX_INSERT		32		/* Nombre d'insertion possible			*/

/* Errors Code	*/
#define CODE_SUCCESS		0
#define ERR_NOT_FOUND		-1
#define ERR_VEC_EMPTY		-2
#define ERR_UNKNOWN			-4

/* Errors Text	*/
#define MSG_NOT_FOUND		"Aucune occurence trouve"
#define MSG_VEC_EMPTY		"Le vecteur est vide"
#define MSG_NOT_ORD			"Le vecteur n'est pas trie"
#define MSG_ALREADY_ORD		"Le vecteur est deja trie"
#define MSG_VECT_FULL		"Le vecteur est plein"
#define MSG_UNK_CHOICE		"Choix invalide"

/* Menu KeyCode */
#define MENU_ENCODE		1	/* Encoder le vecteur			*/
#define MENU_DISPLAY	2	/* Afficher le vecteur			*/
#define MENU_ORDER		3	/* Trier le vecteur				*/
#define MENU_INSERT		4	/* Inrérer un élement			*/
#define MENU_FIND		5	/* Trouver une occurence		*/
#define MENU_DSPM		6	/* Force l'affichage du menu	*/
#define MENU_EXIT		7	/* Hum... Quitter sans doute :D	*/