#include <stdlib.h>

size_t BuildIndex(ouvrier_t *ouvrier, index_t *index);
void ShowFormated(ouvrier_t *ouvrier);
void ShowDataFromIndex(index_t *index);
void ShowDataFromTable(ouvrier_t *ouvrier);
void Index_Insert(index_t *start, index_t insert, short last);
void Index_Sort(index_t *index);
void ShowIndexPointers(index_t *index);