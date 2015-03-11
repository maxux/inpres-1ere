#ifndef __W32CONSOLE_HEADER
	#define __W32CONSOLE_HEADER
	#include <stdio.h>
	#include <string.h>
	#include <windows.h>
	#include <conio.h>

	#define snprintf _snprintf

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

	#define KEYCODE_ENTER   13
	#define KEYCODE_ESC     27
	#define KEYCODE_BACKSP  8
	#define KEYCODE_TAB     9

	#define KEYCODE_SPKEY	-32
	#define KEYCODE_F12		-122
	#define KEYCODE_UP		72
	#define KEYCODE_DOWN	80

	#define _BORDER_HORZ_LINE	'Ä'
	#define _BORDER_VERT_LINE	'³'
	#define _BORDER_TOP_LEFT	'Ú'
	#define _BORDER_TOP_RIGHT	'¿'
	#define _BORDER_BOT_LEFT	'À'
	#define _BORDER_BOT_RIGHT	'Ù'
	#define _DOUBLE_BORDER_HORZ_LINE	'Í'

	#define CURSOR_MAX_LEVEL	64
	#define BUFFER_MAX_LEVEL	8

	#ifndef __WIN32_HEADER_CONSOLE
		typedef struct {
			COORD from;
			COORD size;
			SMALL_RECT rect;

			COORD cursor[CURSOR_MAX_LEVEL];
			CHAR_INFO buffer[BUFFER_MAX_LEVEL][TERM_SIZE];
			/* Warning: sizeof(CHAR_INFO) = 4 */
			/* 8*80*24*4 = 61440 = 60 ko      */

			short b_level;
			short c_level;

		} console_t;

		#define __WIN32_HEADER_CONSOLE
	#endif

	/* Variable Globale Console Win32 */
	console_t wconsole;

	/* Cursor Management */
	void ChangeCurPosition(short x, short y);
	CONSOLE_SCREEN_BUFFER_INFO GetConsoleNfo();
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
#endif