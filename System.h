#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cores da consola (baseadas no ConsoleColor do C#)
typedef enum {
    Black = 0,
    DarkBlue,
    DarkGreen,
    DarkCyan,
    DarkRed,
    DarkMagenta,
    DarkYellow,
    Gray,
    DarkGray,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Yellow,
    White
} ConsoleColor;
// --- ENUM DE TECLAS ---
typedef enum {
    Key_None     = 0,
    Key_Backspace = 8,
    Key_Tab       = 9,
    Key_Enter     = 13,
    Key_Escape    = 27,
    Key_Space     = 32,

    Key_0 = '0',
    Key_1 = '1',
    Key_2 = '2',
    Key_3 = '3',
    Key_4 = '4',
    Key_5 = '5',
    Key_6 = '6',
    Key_7 = '7',
    Key_8 = '8',
    Key_9 = '9',

    Key_A = 'A',
    Key_B = 'B',
    Key_C = 'C',
    Key_D = 'D',
    Key_E = 'E',
    Key_F = 'F',
    Key_G = 'G',
    Key_H = 'H',
    Key_I = 'I',
    Key_J = 'J',
    Key_K = 'K',
    Key_L = 'L',
    Key_M = 'M',
    Key_N = 'N',
    Key_O = 'O',
    Key_P = 'P',
    Key_Q = 'Q',
    Key_R = 'R',
    Key_S = 'S',
    Key_T = 'T',
    Key_U = 'U',
    Key_V = 'V',
    Key_W = 'W',
    Key_X = 'X',
    Key_Y = 'Y',
    Key_Z = 'Z',
} ConsoleKey;

void Console_SetCursorPosition(int x,int y);
char Console_ReadKey();
void Console_ResetColor();
void Console_ForegroundColor(ConsoleColor color);
void Console_BackgroundColor(ConsoleColor color);
void Console_Clear();
void Console_Beep();
char Console_Read();
char* Console_ReadLine();
void Console_WriteLine(const char* texto);
void Console_Write(const char* texto);
char* File_ReadAllText(const char* path);
int File_WriteAllText(const char* path);

#endif
