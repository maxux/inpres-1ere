#define _CRT_SECURE_NO_WARNINGS
#include "UnixConsole.h"

/*
   Chage la position du curseur sur la console WIN32
   @args : position en X et Y
*/
void ChangeCurPosition(short x, short y) {
	printf("\033[%d;%dH", x, y);
}

COORD GetCursorPosition() {
	COORD temp;

	temp.X = 0;
	temp.Y = 0;

	return temp;
}

int my_outc(int c) {
	static int tty = 0;

	if (!tty)
		tty = open("/dev/tty", O_WRONLY);
	
	if(write(tty, &c, 1) != 1)
		return 1;
	else
		return 0;
}

void apply_term(char *term) {
	char *s;
	char buff[4096];
	char *ptr_buff;

	ptr_buff = buff;
	(void)memset(buff, '\0', 4096);
	if((s = tgetstr(term, &ptr_buff)))
		tputs(s, STDOUT_FILENO, my_outc);
}

/* Affiche ou cache le curseur de la console */
/* @args : état du curseur                   */
void ShowConsoleCursor(unsigned char show) {
	if(show)
		apply_term("ve");
	else
		apply_term("vi");
}

/*
   Efface un nombre de caractère sur la ligne en cours de la console WIN32
   @args : nbr de case à éffacer
*/
void ClearBackSpace(short count) {
	short i;

	printf("\033[%dC", count); /* Forward */

	for(i = 0; i < count; i++)
		printf(" ");

	printf("\033[%dC", count);
}

/*
   Permet d'éffacer une date avec gestion des / de séparation WIN32
*/
void ClearBackSpaceDate() {
	printf("\033[2C");
	printf(" /");
	printf("\033[2C");
}

/*
   Change la couleur du curseur WIN32
   @args : Couleur d'écrire, coleur de fond (define C_FORE_ et C_BACK_)
*/
void SetColor(int fore, int back) {
/*	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H, back * 16 + fore); */
}

/*
   Change la couleur du curseur en gris/noir
*/
void ResetColor() {
	/* SetColor(C_FORE_GREY, C_BACK_BLACK); */
}

/* Défini la taille de la console              */
/* @args : nombre de colones, nombre de lignes */
void SetConsoleSize(short rows, short lines) {
	printf("\033[8;%d;%d;t", lines, rows);
}

/* Efface l'écran */
void ClearScreen() {
	printf("\033[2J\033[K");
}

int _getch() {
	struct termios oldt, newt;
	int ch;
	
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	
	return ch;
}

/* Initialise une structure de console */
/* @args : structure console           */
void W32Console_Init(console_t *console) {
	SetConsoleSize(TERM_COLS, TERM_LINES);
	ClearScreen();

	/* console->rect.Top = 0;
	console->rect.Left = 0;
	console->rect.Right = TERM_COLS;
	console->rect.Bottom = TERM_LINES; */

	console->from.X = 0;
	console->from.Y = 0;

	console->size.X = TERM_COLS;
	console->size.Y = TERM_LINES;
}

/* Sauve l'état de la console (snapshot) */
/* @args : structure de console          */
void W32Console_SaveBuffer(console_t *console) {
	/* console->cursor = GetCursorPosition();
	ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), console->buffer, console->size, console->from, &console->rect); */
}

/* Restaure l'état de la console (snapshot rollback) */
/* @args : structure de console                      */
void W32Console_RestoreBuffer(console_t *console) {
	/* WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), console->buffer, console->size, console->from, &console->rect);
	ChangeCurPosition(console->cursor.X, console->cursor.Y); */
}

/* Converti une chaine ANSI en OEM Console (correction charset) */
/* @args : chaine à corriger                                    */
/* Return: adresse du début de la chaine                        */
char * w(char *data) {
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
