/*
    DEMONSTRATION DU FONCTIONNEMENT DES LISTES DYNAMIQUES
*/

#include <stdio.h>
#include <stdlib.h>
#include "__tables.h"
#include "dynlist.h"
#include "search.h"

/*
 - Le module de liste dynamique permet l'affichage d'un popup/menu à sélection dynamique
 - Le fonctionnement est décrit dans la fonction 'demo()' ci dessous.
 - Le traitement de la liste peut être modifié à l'aide d'une fonction de callback
   (cf dynlist_callback_t)
*/
void __dynlist_demo() {
	dynlist_t *mylist;                    /* Pointeur vers la liste qu'on va utiliser */
	dynlist_node_t *returned = NULL;      /* Pointeur vers le noeud de retour -> Contiendra l'élement sélectionné */
	/* ATTENTION: Pour une première utilisation, le pointeur DOIS pointer vers NULL ! */

	mylist = DynamicList_Create(DYNLIST_INFO);     /* Création de la liste. */
	// DynamicList_AppendNode(mylist, 1, "Hello");     /* Ajout du noeud 'Hello' avec l'id 1 */
	// DynamicList_AppendNode(mylist, 2, "World");     
	// DynamicList_AppendNode(mylist, 3, "How");
	/* Les dépassement seront ignorés */
	// DynamicList_AppendNode(mylist, 4, "Test de depassement de ma chaine, avec une chaine trop longue");

	/* Affichage de la liste. La valeur de retour sera mise dans 'returned'.
	   ATTENTION: returned sera créé dynamiquement si il vaut NULL, sinon il sera utilisé supposant qu'il est alloué
	   -> Ne pas oublier de le détruire une fois terminé.
	*/
	// returned = DynamicList_Process(mylist, returned);
	DynamicList_Info(mylist);

	/* Libération de la mémoire. DynamicList_Free désalloue tout les nodes ainsi que la liste */
	// DynamicList_Free(mylist);

	/* Affichage de la valeur retournée */
	// printf("RETURN: %d / %s\n", returned->id, returned->text);

	/* Nettotage du noeud de résultat */
	// DynamicList_FreeNode(returned);
}

void __demo_search(index_t *index, size_t index_size) {
	int iter;
	search_t data;

	data = Search_Create();
	Searching(index, "BOVY", index_size, &data);
	
	if(data.data != NULL) {
		iter = data.nbresult;
		printf("%d::\n", iter);

		while(iter-- >= 0) {
			printf("%s - %s\n", data.data->nom, data.data->prenom);
			data.data++;
		}

	} else printf("NO RESULT\n");

	Search_Free(&data);

	data = Search_Create();
	Searching(index, "FIRKET", index_size, &data);
	
	if(data.data != NULL) {
		iter = data.nbresult;
		printf("%d::\n", iter);

		while(iter-- >= 0) {
			printf("%s - %s\n", data.data->nom, data.data->prenom);
			data.data++;
		}

	} else printf("NO RESULT\n");

	Search_Free(&data);

	data = Search_Create();
	Searching(index, "FAIL", index_size, &data);
	
	if(data.data != NULL) {
		iter = data.nbresult;
		printf("%d::\n", iter);

		while(iter-- >= 0) {
			printf("%s - %s\n", data.data->nom, data.data->prenom);
			data.data++;
		}

	} else printf("NO RESULT\n");

	Search_Free(&data);

	getchar();
}