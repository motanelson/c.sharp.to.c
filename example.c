#include "System.h"
#include "System.IO.h"
void Main() {
FILE* ficheiro = fopen("out.txt", "r");
if (ficheiro == NULL) {
    printf("Erro ao abrir o ficheiro.\n");
    return;
}
char linha[1024];
while (fgets(linha, sizeof(linha), ficheiro)) {
    printf("%s", linha);
}
fclose(ficheiro);