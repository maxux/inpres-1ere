// #define _CRT_SECURE_NO_WARNINGS

#include "Win32Console.h"

/*
   Chage la position du curseur sur la console WIN32
   @args : position en X et Y
*/
void ChangeCurPosition(short x, short y) {
	COORD Position;

	Position.X = x;
	Position.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
}

/*
   Retourne un handle sur la console en cours WIN32
*/
CONSOLE_SCREEN_BUFFER_INFO GetConsoleNfo() {
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO cInfos;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &cInfos);

	return cInfos;
}

/*
   Récupère la position actuelle du curseur sur la console WIN32
   return: position actuelle du curseur
*/
COORD GetCursorPosition() {
	CONSOLE_SCREEN_BUFFER_INFO cInfos;
	cInfos = GetConsoleNfo();
	return cInfos.dwCursorPosition;
}

/*
   Efface un nombre de caractère sur la ligne en cours de la console WIN32
   @args : nbr de case à éffacer
*/
void ClearBackSpace(short count) {
	short i;
	COORD Cur;

	Cur = GetCursorPosition();
	ChangeCurPosition(Cur.X - count, Cur.Y);

	for(i = 0; i < count; i++)
		printf(" ");

	ChangeCurPosition(Cur.X - count, Cur.Y);
}

/*
   Permet d'éffacer une date avec gestion des / de séparation WIN32
*/
void ClearBackSpaceDate() {
	COORD Cur;

	Cur = GetCursorPosition();
	ChangeCurPosition(Cur.X - 2, Cur.Y);
	printf(" /");

	ChangeCurPosition(Cur.X - 2, Cur.Y);
}

/*
   Change la couleur du curseur WIN32
   @args : Couleur d'écrire, coleur de fond (define C_FORE_ et C_BACK_)
*/
void SetColor(int fore, int back) {
	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H, back * 16 + fore);
}

/*
   Change la couleur du curseur en gris/noir
*/
void ResetColor() {
	SetColor(C_FORE_GREY, C_BACK_BLACK);
}

/* Prochainement fonction de convertion d'accents */
// char ascii_ansi[ASCII_REPLACE] = {'é', 'è', 'à'};
// char ascii_cons[ASCII_REPLACE] = {'', '', ''};


/* void SetConsoleSize(short rows, short lines) {
	char *arg;

	arg = (char *) malloc(sizeof(char) * 64);
	_snprintf(arg, 64, "mode con cols=%d lines=%d", rows, lines);

	system(arg);
	free(arg);
} */

/*
   Efface l'écran
*/
void ClearScreen() {
	system("cls");
}
