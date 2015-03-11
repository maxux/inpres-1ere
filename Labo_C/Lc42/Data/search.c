#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include "search.h"
#include "fieldsmanager.h"
#include "misc.h"

/* Fais une recherche dychotomique */
/* @args: l'index dans lequel chercher, la cible, un champs
          de recherche de retour (contiendra les résultats) */
void Searching(index_t *index, char *target, search_t *output) {
	size_t left, right, center, len;
	index_node_t *first, *ptr, *temp;
	short found;

	/* Checking Wildcard */
	len   = strlen(target);
	first = index->nodes;

	/* Init Range */
	left  = 0;
	right = index->size - 1;

	found = 1;
	
	while(left != right) {
		center = (left + right) / 2;
		ptr = first + center;

		/* Compare elements */
		found = strncmp(target, ptr->key, len);
		
		if(found <= 0)
			right = center;
		else
			left = center + 1;
	}

	ptr = first + left;

	if(strncmp(target, ptr->key, len) == 0) {
		/* Now we know that we point to the first element */
		while((strncmp(ptr->key, target, len) == 0) && ptr <= (first + index->size)) {
			output->nbresult++;		/* Initialized with -1 */
			output->data->size++;

			/* Growing index */
			output->data->nodes = (index_node_t *) realloc(output->data->nodes, sizeof(index_node_t) * (output->nbresult + 1));
			if(output->data->nodes == NULL)
				Exit_Fail();

			/* Copy element to result index */
			temp = output->data->nodes + output->nbresult;
			/* temp->key = (char *) malloc(sizeof(char) * (strlen(ptr->key) + 1));
			if(temp->key == NULL)
				Exit_Fail();
			*/

			strncpy(temp->key, ptr->key, (strlen(ptr->key) + 1));
			temp->offset = ptr->offset;
			
			ptr++;
		}
	}
}

/* Demande à l'utilisateur un champs de recherche, effectue la recherche */
/* @args : l'index dans lequel chercher                                  */
/* Return: un résultat de type recherche                                 */
search_t * User_Search(index_t *index) {
	search_t *result;
	field_t *input;
	char *buffer;

	buffer = (char *) malloc(sizeof(char) * SEARCH_MAXLEN);
	if(buffer == NULL)
		Exit_Fail();

	*buffer = '\0';

	input = Fields_Create();
	Fields_AppendNode(input, "Index", buffer, SEARCH_MAXLEN, FIELD_UPPER, FIELD_RESTRICT_ALLOW);

	ClearScreen();
	Fields_Process(input);
	Fields_Free(input);

	result = Search_Create();
	strcpy(result->data->filename, index->filename);

	Searching(index, buffer, result);

	free(buffer);
	return result;
}

/* Crée une recherche vide        */
/* Return: l'adresse de la struct */
search_t * Search_Create() {
	search_t *_new;

	_new = (search_t *) malloc(sizeof(search_t));

	if(_new == NULL)
		Exit_Fail();

	_new->data = (index_t *) malloc(sizeof(index_t));
	if(_new->data == NULL)
		Exit_Fail();

	_new->data->size  = 0;
	_new->data->nodes = NULL;
	_new->nbresult    = -1;

	return _new;

}

/* Libère la mémoire alloué à une recherche */
/* @args : la recherche                     */
void Search_Free(search_t *group) {
	if(group->data != NULL)
		Index_Free(group->data);

	free(group);
}