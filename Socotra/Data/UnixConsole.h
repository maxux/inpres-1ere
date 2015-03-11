#ifndef __W32CONSOLE_HEADER
	#define __W32CONSOLE_HEADER
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
	#include <curses.h>
	#include <termios.h>
	#include <termcap.h>
	#include <fcntl.h>

	#ifndef TIOCGETA
		#define TIOCGETA TCGETS
		#define TIOCSETA TCSETS
	#endif /* !TIOCGETA */

	#define TERM_COLS	80
	#define TERM_LINES	24
	#define TERM_SIZE	TERM_COLS * TERM_LINES

	#define C_RESET				0
	#define C_BACK_BLACK 		0
	#define C_BACK_DARKGREEN	2
	#define C_BACK_DARKRED		4
	#define C_BACK_GREY			7
	#define C_BACK_DARKGREY		8
	#define C_BACK_BLUE			9
	#define C_BACK_GREEN		10
	#define C_BACK_LIGHTBLUE	11
	#define C_BACK_RED			12
	#define C_BACK_YELLOW		14
	#define C_BACK_WHITE		15

	#define C_RESET				0
	#define C_FORE_BLACK 		0
	#define C_FORE_DARKGREEN	2
	#define C_FORE_DARKRED		4
	#define C_FORE_GREY			7
	#define C_FORE_DARKGREY		8
	#define C_FORE_BLUE			9
	#define C_FORE_GREEN		10
	#define C_FORE_LIGHTBLUE	11
	#define C_FORE_RED			12
	#define C_FORE_YELLOW		14
	#define C_FORE_WHITE		15

	#define KEYCODE_ENTER   10
	#define KEYCODE_ESC     27
	#define KEYCODE_BACKSP  8
	#define KEYCODE_TAB     9

	#define _BORDER_HORZ_LINE	'-'
	#define _BORDER_VERT_LINE	'|'
	#define _BORDER_TOP_LEFT	'+'
	#define _BORDER_TOP_RIGHT	'+'
	#define _BORDER_BOT_LEFT	'+'
	#define _BORDER_BOT_RIGHT	'+'

	#ifndef __WIN32_HEADER_CONSOLE
		typedef struct {
			short X;
			short Y;
		} COORD;

		typedef struct {
			COORD from;
			COORD size;
			short rect;
			char buffer[TERM_SIZE];
			/* SMALL_RECT rect;
			CHAR_INFO buffer[TERM_SIZE]; */
			COORD cursor;
			/* CHAR_INFO *buffer[TERM_SIZE];
			COORD *cursor;
			int level; */

		} console_t;

		#define __WIN32_HEADER_CONSOLE
	#endif

	console_t wconsole;
	
	/* Cursor Management */
	void ChangeCurPosition(short x, short y);
	COORD GetCursorPosition();
	void ShowConsoleCursor(unsigned char show);

	/* Erasing */
	void ClearBackSpace(short count);
	void ClearBackSpaceDate();
	void ClearScreen();

	/* Colors */
	void SetColor(int fore, int back);
	void ResetColor();

	/* Settings */
	void W32Console_Init(console_t *console);
	void SetConsoleSize(short rows, short lines);

	/* Buffer */
	void W32Console_SaveBuffer(console_t *console);
	void W32Console_RestoreBuffer(console_t *console);

	/* Charset / Print */
	char * w(char *data);
	void PrintCenter(char data[]);

	int _getch();
#endif
