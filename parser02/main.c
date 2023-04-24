#include "tinyexpr.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	//para outros resultados mude a linha 7, por exemplo, se quiser o fatorial de 5, coloque: const char *c = "fatorial(5)";
    const char *c = "fatorial(2)";
    double r = te_interp(c, 0);
    printf("A expressão:\n\t%s\n resulta em:\n\t%f\n", c, r);
    return 0;
}