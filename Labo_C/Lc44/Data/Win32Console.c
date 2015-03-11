#define _CRT_SECURE_NO_WARNINGS
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

/* Affiche ou cache le curseur de la console */
/* @args : état du curseur                   */
void ShowConsoleCursor(unsigned char show) {
	CONSOLE_CURSOR_INFO 	cursorInfo;

	cursorInfo.dwSize   = 10;
	cursorInfo.bVisible = show;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
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

/* Défini la taille de la console              */
/* @args : nombre de colones, nombre de lignes */
void SetConsoleSize(short rows, short lines) {
	char arg[64];

	_snprintf(arg, 64, "mode con cols=%d lines=%d", rows, lines);
	system(arg);
}

/* Efface l'écran */
void ClearScreen() {
	system("cls");
}

/* Initialise une structure de console */
/* @args : structure console           */
void W32Console_Init(console_t *console) {
	SetConsoleSize(TERM_COLS, TERM_LINES);

	console->rect.Top = 0;
	console->rect.Left = 0;
	console->rect.Right = TERM_COLS;
	console->rect.Bottom = TERM_LINES;

	console->from.X = 0;
	console->from.Y = 0;

	console->size.X = TERM_COLS;
	console->size.Y = TERM_LINES;

	console->cursor[0] = GetCursorPosition();

	console->c_level = 0;
	console->b_level = 0;
}

/* Sauve l'état de la console (snapshot) */
/* @args : structure de console          */
void W32Console_SaveBuffer(console_t *console) {
	if(console->c_level < CURSOR_MAX_LEVEL - 1 || console->b_level < BUFFER_MAX_LEVEL - 1) {
		console->c_level++;
		console->b_level++;

		console->cursor[console->c_level] = GetCursorPosition();
		ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), console->buffer[console->b_level], console->size, console->from, &console->rect);
	}
}

/* Restaure l'état de la console (snapshot rollback) */
/* @args : structure de console                      */
void W32Console_RestoreBuffer(console_t *console) {
	if(console->c_level > 0 && console->b_level > 0) {
		WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), console->buffer[console->b_level], console->size, console->from, &console->rect);
		ChangeCurPosition(console->cursor[console->c_level].X, console->cursor[console->c_level].Y);

		console->c_level--;
		console->b_level--;
	}
}

/* Converti une chaine ANSI en OEM Console (correction charset) */
/* @args : chaine à corriger                                    */
/* Return: adresse du début de la chaine                        */
char * w(char *data) {
	char *str;

	/* ANSI - OEM: Converting table */
	unsigned int oem[128]={
		199, 252, 233, 226, 228, 224, 229, 231, /* # 128 - 135 */
		234, 235, 232, 239, 238, 236, 196, 197, /* # 136 - 143 */
		201, 181, 198, 244, 247, 242, 251, 249, /* # 144 - 151 */
		223, 214, 220, 243, 183, 209, 158, 159, /* # 152 - 159 */
		255, 173, 155, 156, 177, 157, 188, 21,  /* # 160 - 167 */
		191, 169, 166, 174, 170, 237, 189, 187, /* # 168 - 175 */
		248, 241, 253, 179, 180, 230, 20,  250, /* # 176 - 183 */
		184, 185, 167, 175, 172, 171, 190, 168, /* # 184 - 191 */
		192, 193, 194, 195, 142, 143, 146, 128, /* # 192 - 199 */
		200, 144, 202, 203, 204, 205, 206, 207, /* # 200 - 207 */
		208, 165, 210, 211, 212, 213, 153, 215, /* # 208 - 215 */
		216, 217, 218, 219, 154, 221, 222, 225, /* # 216 - 223 */
		133, 160, 131, 227, 132, 134, 145, 135, /* # 224 - 231 */
		138, 130, 136, 137, 141, 161, 140, 139, /* # 232 - 239 */
		240, 164, 149, 162, 147, 245, 148, 246, /* # 240 - 247 */
		176, 151, 163, 150, 129, 178, 254, 152  /* # 248 - 255 */
	};

	str = data;

	while(*str != '\0') {
		if(*str < 0)
			*str = oem[((unsigned char)(*str)) - 128];


		str++;
	}

	return data;
}

/* Affiche du texte, centré à l'écran */
/* @args : la chaine                  */
void PrintCenter(char data[]) {
	short i;

	i = (TERM_COLS / 2) - (strlen(data) / 2);
	while(i-- > 0)
		printf(" ");

	printf("%s", data);
}