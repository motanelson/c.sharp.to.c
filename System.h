#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Console_Clear();
void Console_Beep();
void Console_WriteLine(const char* texto);
char* File_ReadAllText(const char* path);
int File_WriteAllText(const char* path);

#endif
