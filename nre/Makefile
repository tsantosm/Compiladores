all: delete main clean

binario:
	gcc -W -Wall gerarBinario.c -o gerarBinario
	clear

clean:
	clear

delete: 
	@rm -rf src/*.o

main: nre.c
	gcc -W -Wall nre.c -o nre
