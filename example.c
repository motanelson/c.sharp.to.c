#include "System.h"
#include "System.IO.h"
void Main() {
Console_Clear();
char* conteudo = File_ReadAllText("out_txt");
Console_WriteLine(conteudo);
File_WriteAllText("out_dat", conteudo);