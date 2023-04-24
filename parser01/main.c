#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 1000

typedef enum Token {
    NumeroInteiro,
    NumeroReal,
    Soma,
    Indeterminado
} Token;

struct Tokens {
    enum Token token;
    union {
        char op;
        double num;
    } value;
};

void tokenizar(char *caracteres, int length, struct Tokens *vetorTokens, int *numTokens) {
    int i = 0;
    int j = 0;
    char token[MAX_SIZE];

    while (i < length) {
        int tokenLength = 0;

        while (isspace(caracteres[i])) {
            i++;
        }

        if (isdigit(caracteres[i]) || caracteres[i] == '.') {
            while (isdigit(caracteres[i]) || caracteres[i] == '.') {
                token[tokenLength++] = caracteres[i++];
            }
            token[tokenLength] = '\0';

            if (strchr(token, '.') == NULL) {
                vetorTokens[j].token = NumeroInteiro;
                vetorTokens[j].value.num = atoi(token);
            } else {
                vetorTokens[j].token = NumeroReal;
                vetorTokens[j].value.num = atof(token);
            }

            j++;
        } else if (caracteres[i] == '+') {

            vetorTokens[j].token = Soma;
            vetorTokens[j].value.op = '+';
            i++;
            j++;
        } else {

            vetorTokens[j].token = Indeterminado;
            vetorTokens[j].value.op = caracteres[i++];
            j++;
        }
    }

    *numTokens = j;
}

int main(int argc, char **argv) {
    char content[MAX_SIZE];
    FILE *fp;
    int i = 0;

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(content, MAX_SIZE, fp) != NULL) {
        for (i = 0; content[i] != '\0'; i++);
    }

    fclose(fp);

    struct Tokens vetorTokens[MAX_SIZE];
    int numTokens = 0;

    tokenizar(content, i, vetorTokens, &numTokens);

    double resultado = 0.0;
    int sinal = 1;

    for (int k = 0; k < numTokens; k++) {
        if (vetorTokens[k].token == Soma) {
            sinal = 1;
        } else if (vetorTokens[k].token == NumeroInteiro || vetorTokens[k].token == NumeroReal) {
            resultado += sinal * vetorTokens[k].value.num;
        }
    }

    printf("O resultado é: %f\n", resultado);

    return 0;
}