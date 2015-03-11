typedef int (*fctpt)(int *vect, int *nbelem);

int Encodage(int *vect, int *nbelem);
int Affichage(int *vect, int *nbelem);
void Insert(int *vect, int insert, int nbelem);
int TriInsert(int *vect, int *nbelem);
int Somme(int *vect, int *nbelem);
void RunLoop(int *vect, int nbelem, fctpt *ptf);