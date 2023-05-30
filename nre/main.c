#include <stdio.h>
#include <stdint.h>

#define MAX_TAMANHO 255
#define HEADER 42   
#define HLT 240

void lerBinario(char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "rb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    static uint8_t c[MAX_TAMANHO];
    size_t bytesLidos = fread(c, sizeof(uint8_t), MAX_TAMANHO, f);
    fclose(f);

    if (c[0] != HEADER) {
        printf("Rejeitado! O primeiro byte deve ser 42.\n");
        return;
    }

    for (size_t i = 0; i < bytesLidos && c[i] != HLT; i++) {
        printf("%u ", c[i]);
    }
    
    printf("\n");
}

void executarInstrucoes(uint8_t *instrucoes, size_t tamanho) {
    uint8_t acumulador = 0;
    uint8_t contadorPrograma = 0;

    while (contadorPrograma < tamanho && instrucoes[contadorPrograma] != HLT) {
        switch (instrucoes[contadorPrograma]) {
            case 16:  // STA
                contadorPrograma++;
                instrucoes[instrucoes[contadorPrograma]] = acumulador;
                break;
                
            case 32:  // LDA
                contadorPrograma++;
                acumulador = instrucoes[instrucoes[contadorPrograma]];
                break;
            
            case 48:  // ADD
                contadorPrograma++;
                acumulador += instrucoes[instrucoes[contadorPrograma]];
                break;

            case 64:  // OR
                contadorPrograma++;
                acumulador |= instrucoes[instrucoes[contadorPrograma]];
                break;

            case 80:  // AND
                contadorPrograma++;
                acumulador &= instrucoes[instrucoes[contadorPrograma]];
                break;

            case 96:  // NOT
                acumulador = ~acumulador;
                break;

            case 128:  // JMP
                contadorPrograma++;
                contadorPrograma = instrucoes[contadorPrograma];
                contadorPrograma--;  // Para compensar o incremento no laço while
                break;

            case 144:  // JN
                contadorPrograma++;
                if (acumulador >> 7) {  // Verifica se o bit de sinal é 1
                    contadorPrograma = instrucoes[contadorPrograma];
                    contadorPrograma--;  // Para compensar o incremento no laço while
                }
                break;
            
            case 160:  // JZ
                if (acumulador == 0) {
                    contadorPrograma++;
                    contadorPrograma = instrucoes[contadorPrograma];
                    contadorPrograma--;  // Para compensar o incremento no laço while
                }
                break;
        }

        contadorPrograma++;
    }

    printf("\nACUMULADOR: %u\n", acumulador);
    printf("Contador de programa: %u\n", contadorPrograma);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: %s <nome do arquivo>\n", argv[0]);
        return 1;
    }
    
    uint8_t instrucoes[MAX_TAMANHO];
    size_t bytesLidos = 0;

    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    
    bytesLidos = fread(instrucoes, sizeof(uint8_t), MAX_TAMANHO, f);
    fclose(f);

    if (instrucoes[0] != HEADER) {
        printf("Rejeitado! O primeiro byte deve ser 42.\n");
        return 1;
    }

    printf("Instruções lidas do arquivo:\n");
    for (size_t i = 0; i < bytesLidos && instrucoes[i] != HLT; i++) {
        printf("%u ", instrucoes[i]);
    }
    
    printf("\n");

    executarInstrucoes(instrucoes, bytesLidos);
    
    return 0;
}
