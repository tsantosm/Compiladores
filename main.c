#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    Mais,
    Menos,
    Multiplicacao,
    Divisao,
    Potenciacao,
    Inteiro,
    Flutuante,
    Indeterminado
} Token;

int tokenizar(const char* s, Token* tokens, int max_tokens) {
    int tokens_len = 0;
    while (*s && tokens_len < max_tokens) {
				if (isdigit(*s) || (*s == '-' && isdigit(*(s+1)))) {
				    int len = strcspn(s, " +-*/^");
				    char* endptr;
				    double num = strtod(s, &endptr);
					    if (endptr - s == len && strchr(s, '.') == NULL) {
					        tokens[tokens_len++] = Inteiro;
					    } else {
					        tokens[tokens_len++] = Flutuante;
					    }
					    s = endptr;
					} 
			 else {
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
			    }
    return tokens_len;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Arquivo nao encontrado\n");
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
    printf("Interpretando o arquivo '%s':\n", argv[1]);
    
    while (fgets(input, sizeof(input), arquivo)) {
        input[strcspn(input, "\n")] = '\0';

        int tokens_len = tokenizar(input, tokens, 100);

        printf("Tokens Interpretados:\n");

        for (int i = 0; i < tokens_len; i++) {
            switch (tokens[i]) {
                case Mais: printf("+ Mais\n"); break;
                case Menos: printf("- Menos\n"); break;
                case Multiplicacao: printf("* Multiplicação\n"); break;
                case Divisao: printf("/ Divisão\n"); break;
                case Potenciacao: printf("** Potenciação\n"); break;
                case Inteiro: printf("Número inteiro\n"); break;
                case Flutuante: printf("Número em ponto flutuante\n");break;
            }
        }
    }
    
    fclose(arquivo);
    return 0;
}
