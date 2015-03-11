void EncodeFiche(FICHE *data, short nbname);
void BuildIndex(FICHE *data, INDEX *idx, short nbname);
void PrintFiche(FICHE *data);
void PrintFicheByIndex(INDEX *idx);
void InsertStruct(INDEX **index, INDEX *insert, short last);
void OrderStruct(INDEX **idx);
