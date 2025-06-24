#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

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


#define BLOCO_TAMANHO 4096

void Console_Clear() {
    for (int i = 0; i < 500; i++) {
        printf("\n");
    }
}
void Console_Beep() {
    printf("\a");
    fflush(stdout);  // Garante que o som é enviado imediatamente
}
char* Console_ReadLine() {
    char* buffer = malloc(BLOCO_TAMANHO);
    if (!buffer) return NULL;

    if (fgets(buffer, BLOCO_TAMANHO, stdin) == NULL) {
        free(buffer);
        return NULL;
    }

    // Remove newline se presente
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return buffer;
}
char Console_Read() {
    int c = getc(stdin);
    if (c == EOF) {
        return '\0';  // ou um valor especial, como -1, se quiseres
    }
    return (char)c;
}
char Console_ReadKey() {
    int c = getc(stdin);
    if (c == EOF) {
        return '\0';  // ou um valor especial, como -1, se quiseres
    }
    return (char)c;
}
char *ToString(double numero) {
    char *buffer = (char *)malloc(1024); // Aloca 1024 caracteres
    if (buffer == NULL) {
        return NULL; // Falha na alocação
    }

    sprintf(buffer, "%.2f", numero); // Converte o inteiro para string
    return buffer;
}

void Console_WriteLine(const char* texto) {
    printf("%s\n", texto);
}

void Console_Write(const char* texto) {
    printf("%s", texto);
    fflush(stdout);
}

char* File_ReadAllText(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) {
        printf("Erro ao abrir o ficheiro: %s\n", path);
        return NULL;
    }

    size_t capacidade = BLOCO_TAMANHO;
    size_t tamanho = 0;
    char* buffer = malloc(capacidade);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    size_t lido;
    while ((lido = fread(buffer + tamanho, 1, BLOCO_TAMANHO, f)) > 0) {
        tamanho += lido;
        if (tamanho + BLOCO_TAMANHO > capacidade) {
            capacidade += BLOCO_TAMANHO;
            char* novo = realloc(buffer, capacidade);
            if (!novo) {
                free(buffer);
                fclose(f);
                return NULL;
            }
            buffer = novo;
        }
    }

    buffer[tamanho] = '\0';  // Terminar como string
    fclose(f);
    return buffer;
}

int File_WriteAllText(const char* path, const char* conteudo) {
    FILE* f = fopen(path, "w");
    if (!f) {
        printf("Erro ao criar o ficheiro: %s\n", path);
        return 0;
    }

    fputs(conteudo, f);
    fclose(f);
    return 1;
}
void Console_BackgroundColor(ConsoleColor color) {
    int a=0;
    int r=(4 & color)>>2;
    int g= 2 & color;
    int b=(1 & color)<<2;
    a=r | g | b;
    int n = 40 + ((a) & 7 % 8);  // ANSI base para background (cores normais)
    printf("\033[%dm", n);

    if (color >= 8) {
        printf("\033[1m"); // brilhante se for "High" color
    }

    fflush(stdout);  // aplica imediatamente
}
void Console_ForegroundColor(ConsoleColor color) {
    int a=0;
    int r=(4 & color)>>2;
    int g= 2 & color;
    int b=(1 & color)<<2;
    a=r | g | b;
    int n = 30 + ((a) & 7 % 8);  // ANSI base para background (cores normais)
    printf("\033[%dm", n);

    if (color >= 8) {
        printf("\033[1m"); // brilhante se for "High" color
    }

    fflush(stdout);  // aplica imediatamente
}
void Console_ResetColor() {
    
    printf("\033[37;40m");
    
    fflush(stdout);  // aplica imediatamente
}
void Console_SetCursorPosition(int x,int y) {
    printf("\033[%d;%dd", y,x);
    fflush(stdout);  // aplica imediatamente
}
int Random_Next(int n){
    srand(time(NULL));
    return rand() % n;

}
double Random_NextDouble(){
    srand(time(NULL));
    return (double)rand() / (double)RAND_MAX;

}

