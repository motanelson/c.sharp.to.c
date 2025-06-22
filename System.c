#include "System.h"

void Console_Clear() {
    for (int i = 0; i < 500; i++) {
        printf("\n");
    }
}

void Console_WriteLine(const char* texto) {
    printf("%s\n", texto);
}

FILE* File_ReadAllText(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) {
        printf("Erro ao abrir o ficheiro: %s\n", path);
        return NULL;
    }
    return f;
}

FILE* File_WriteAllText(const char* path) {
    FILE* f = fopen(path, "w");
    if (!f) {
        printf("Erro ao criar o ficheiro: %s\n", path);
        return NULL;
    }
    return f;
}
