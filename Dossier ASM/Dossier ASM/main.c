#include <stdio.h>
#include <stdlib.h>

/* Prototypes */
void fUnion(int *t1, int *t2, int *tres);
void fInter(int *t1, int *t2, int *tres);
void fDiff(int *t1, int *t2, int *tres);
void fPCart(int *t1, int *t2, int *tres);
void fAfficher(int *tres);
void fClear(int *tres, int size);

/* Tableaux initiaux */
int t1[] = {1, 5, 7, 8, 10, 12, 4,  13, 45, 20, -1};
int t2[] = {1, 6, 9, 8, 10, 13, 21, 11, 45, 17, -1};

/* Tableaux de pointeurs de fonctions */
void *fcts[] = {fUnion, fInter, fDiff, fPCart, 0};

/* Messages */
char oint[]  = "%d, ";
char omsg[]  = "%s:\n";
char lf[]    = "EOL\n\n";

char *msgs[] = {"Union", "Intersection", "Difference", "(Bonus) Produit Cartesien"};

/* Fonctions */
int main(void) {
	/* sizeof(t1) / sizeof(int) -> nb elem t1 */
	/* prod cartérien demande: (t1 * t2 * 2) + 1 */
	int size_res = (((sizeof(t1) / sizeof(int)) * (sizeof(t2) / sizeof(int)) * 2) + 1) * sizeof(int);
	int *tres;

	_asm {
		/* Alloue le tableau résultant dynamiquement en mémoire */
		mov eax, size_res
		push eax					/* push sizeof malloc */
		mov dword ptr tres, eax		/* requis par malloc  */
		call dword ptr malloc
		add esp, 4					/* clear push */
		mov tres, eax				/* assigne l'addresse */

		/* -- Initialize le vecteur resultant à -1 pour chaque cases */
		/* -> fClear(tres, tsize) */
		shr size_res, 2			/* divise la taille par 4 (sizeof int) */
		push size_res			/* paramètre 2 */
		push tres				/* paramètre 1 */
		call dword ptr fClear
		add esp, 8				/* clear push  */

		/* Indice de fcts */
		xor edi, edi	/* edi est utilisé partout comme indice d'avancement principal du main */
		push tres

		/* -- Boucle sur les fonctions de traitement */
		__fcts_loop:
			cmp fcts[edi], 0
			je __fcts_eof

			push offset t2
			push offset t1
			mov eax, fcts[edi]	/* fcts[edi] */
			call eax			/* *fcts */
			add esp, 8

			/* Affichage du contenu du vecteur */
			/* -> fAfficher(tres) */
			call dword ptr fAfficher

			add edi, 4			/* fcts++ */
			jmp __fcts_loop		/* loop   */

		__fcts_eof:
			/* Enlève 'tres' de la pile */
			add esp, 4

			/* Fin du code */
			push dword ptr tres		/* push l'adresse du malloc */
			call dword ptr free		/* free l'adresse */
			add esp, 4				/* clear push */

			call dword ptr getchar	/* getchar() */

			xor eax, eax			/* valeur du return: 0 */
	}
}

void fUnion(int *t1, int *t2, int *tres) {
	_asm {
		mov eax, t1
		mov ebx, t2
		mov ecx, tres

		/* Copie le premier tableau dans résultat */
		__fUnion_copy_a:
			cmp [eax], -1		/* while(*t1 != -1) */
			je __fUnion_next

			mov edx, [eax]		/* *(tres++) = *(t1++) */
			mov [ecx], edx

			add eax, 4
			add ecx, 4
			jmp __fUnion_copy_a

		/* Pour chaque élement de b, on le cherche dans tres, si il n'y est pas, on l'y ajoute */
		__fUnion_next:
			cmp [ebx], -1		/* while(*t2 != -1) */
			je __fUnion_eof

			mov ecx, tres
			mov edx, [ebx]
			__fUnion_next_cmp:
				cmp [ecx], -1			/* while(*tres != -1) */
				je __fUnion_prep_next

				cmp [ecx], edx			/* if(*tres == *t2) */
				je __fUnion_prep_next

				add ecx, 4				/* else: tres++ */
				jmp __fUnion_next_cmp

			__fUnion_prep_next:			/* Si pas trouvé, ecx se trouve sur la nouvelle case */
				mov [ecx], edx			/* *tres = *t2 */
				add ebx, 4				/* t2++ */
				jmp __fUnion_next

		__fUnion_eof:
			mov [ecx], -1
	}
}

void fInter(int *t1, int *t2, int *tres) {
	_asm {
		mov eax, t1
		mov ebx, t2
		mov ecx, tres

		__fInter_loop:
			cmp [eax], -1		/* while(*t1 != -1) */
			je __fInter_eof
			
			__fInter_loop2:
				cmp [ebx], -1		/* while(*t2 != -1) */
				je __fIner_eoloop2

				mov edx, [eax]
				cmp [ebx], edx			/* if(*t1 == *t2) */
				je __fInter_addit

				add ebx, 4				/* else: t2++ */
				jmp __fInter_loop2

			__fInter_addit:
				mov [ecx], edx			/* *tres = *t1 */
				add ecx, 4				/* tres++      */

			__fIner_eoloop2:
				mov ebx, t2				/* Reset le pointeur t2 */
				add eax, 4				/* t1++ */
				jmp __fInter_loop

		__fInter_eof:
				mov [ecx], -1			/* Fin de tableau */
	}
}

void fDiff(int *t1, int *t2, int *tres) {
	_asm {
		mov eax, t1
		mov ecx, tres

		__fDiff_loop_a:
			cmp [eax], -1		/* while(*t1 != -1) */
			je __fDiff_eof

			mov ebx, t2
			mov edx, [eax]
			__fDiff_loop_b:
				cmp [ebx], -1		/* while(*t2 != -1) */
				je __fDiff_next_a

				cmp [ebx], edx		/* déjà présent */
				je __fDiff_skip

				add ebx, 4			/* t2++ */
				jmp __fDiff_loop_b

				__fDiff_skip:
					add eax, 4		/* t1++ */
					jmp __fDiff_loop_a

			__fDiff_next_a:
				mov [ecx], edx
				add eax, 4
				add ecx, 4
				jmp __fDiff_loop_a

		__fDiff_eof:
			mov [ecx], -1
	}
}

void fPCart(int *t1, int *t2, int *tres) {
	_asm {
		mov eax, t1
		mov ecx, tres

		__fPCart_loop1:
			cmp [eax], -1			/* while(*t1 != -1) */
			je __fPCart_eof

			mov ebx, t2
			__fPCart_loop2:
				cmp [ebx], -1		/* while(*t2 != 2) */
				je __fPCart_eoloop2

				mov edx, [eax]
				mov [ecx], edx		/* *(tres++) = *t1 */
				add ecx, 4

				mov edx, [ebx]
				mov [ecx], edx		/* *(tres++) = *t2 */
				add ecx, 4
				add ebx, 4

				jmp __fPCart_loop2
				
				__fPCart_eoloop2:
					add eax, 4
					jmp __fPCart_loop1

		__fPCart_eof:
			mov [ecx], -1
	}
}

void fAfficher(int *tres) {
	_asm {
		mov ebx, tres

		push dword ptr msgs[edi];	/* push l'adresse du message */
		lea eax, [omsg]				/* Assignation de l'adresse de "%s" */
		push eax					/* Push: l'adresse du string  */
		call dword ptr printf
		add esp, 8					/* Reset le pointeur de pile  */

		__fAfficher_loop:
			cmp [ebx], -1
			je __fAfficher_eof		/* While(*ebx != -1) */

			push dword ptr [ebx];	/* Push: contenu de l'adresse */
			lea eax, [oint]			/* Assignation de l'adresse de "%d," */
			push eax				/* Push: l'adresse du string  */
			call dword ptr printf
			add esp, 8				/* Reset le pointeur de pile  */

			add ebx, 4				/* tres++ */
			jmp __fAfficher_loop

		__fAfficher_eof:			/* Print "\n" */
			lea eax, [lf]
			push eax
			call dword ptr printf
			add esp, 4
	}
}

void fClear(int *tres, int tsize) {
	_asm {
		mov eax, tres
		mov ecx, tsize

		__fInitRes_loop:			/* while(size-- > 0) */
			mov [eax], -1			/* *tres = -1	*/
			add eax, 4				/* tres++		*/
			loop __fInitRes_loop
	}
}