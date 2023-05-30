#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void gerarBinario(char *buffer, int tamanhoBuffer, char *nomeArquivo){
  FILE *f = fopen(nomeArquivo, "wb");
  fwrite(buffer, 1, tamanhoBuffer, f);
  fclose(f);
}

int main() {
  char buffer[13] = {42, 0, 0, 32, 10, 64, 11, 16, 12, 240, 1, 2, 0};

  gerarBinario(buffer, 14, "binario.nar");
  
  return 0;
}