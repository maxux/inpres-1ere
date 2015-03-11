#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

// #define TERM_COLS	80
// #define TERM_LINES	24

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

void ChangeCurPosition(short x, short y);
CONSOLE_SCREEN_BUFFER_INFO GetConsoleNfo();
COORD GetCursorPosition();

void ClearBackSpace(short count);
void ClearBackSpaceDate();

void SetColor(int fore, int back);
void ResetColor();

void ClearScreen();

// void SetConsoleSize(short rows, short lines);
