#include <stdio.h>
#include <string.h>

typedef enum {
    Mais,
    Menos,
    Multiplicacao,
    Divisao,
    Potenciacao,
    Indeterminado
} Token;

int tokenizar(const char* s, Token* tokens, int max_tokens) {
    int tokens_len = 0;
    while (*s && tokens_len < max_tokens) {
        switch (*s) {
            case '+': tokens[tokens_len++] = Mais; break;
            case '-': tokens[tokens_len++] = Menos; break;
            case '*':                
                if (*(s + 1) == '*') {
                    tokens[tokens_len++] = Potenciacao; 
                    s++;
                } else {
                    tokens[tokens_len++] = Multiplicacao;
                }
                break;
            case '/': tokens[tokens_len++] = Divisao; break;
            case ' ': break;
            default: tokens[tokens_len++] = Indeterminado; break;
        }
        s++;
    }
    return tokens_len;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Erro: o programa deve ser chamado com um argumento contendo o nome do arquivo a ser interpretado.\n");
        return 1;
    }
    
    Token tokens[100];
    char input[100];
	
    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo '%s'\n", argv[1]);
        return 1;
    }
    
    printf("Interpretador Lexer em C\n");
//  printf("Caracteres aceitos até o momento: +, -, *, /, ** \n");
    printf("Interpretando o arquivo '%s':\n", argv[1]);
    
    while (fgets(input, sizeof(input), arquivo)) {
        input[strcspn(input, "\n")] = '\0';

        int tokens_len = tokenizar(input, tokens, 100);

        printf("Caracteres Interpretados:\n");

        for (int i = 0; i < tokens_len; i++) {
            switch (tokens[i]) {
                case Mais: printf("+ Mais\n"); break;
                case Menos: printf("- Menos\n"); break;
                case Multiplicacao: printf("* Multiplição\n"); break;
                case Divisao: printf("/ Divisão\n"); break;
                case Potenciacao: printf("** Potenciacao\n"); break;
                case Indeterminado: printf("Indeterminado\n"); break;
            }
        }
    }
    
    fclose(arquivo);
    return 0;
}
