CC=gcc
CFLAGS=-Wall -Werror -pedantic -std=c11

build: main

main: main.c
	$(CC) $(CFLAGS) main.c -o main