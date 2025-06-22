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
void Console_ForegroundColor(ConsoleColor color);
void Console_BackgroundColor(ConsoleColor color);
void Console_Clear();
void Console_Beep();
char Console_Read();
char* Console_ReadLine();
void Console_WriteLine(const char* texto);
char* File_ReadAllText(const char* path);
int File_WriteAllText(const char* path);

#endif
