CC=gcc
CFLAGS= -Wall

all: compiler

compiler: compiler.o
	$(CC) compiler.o -o compiler

compiler.o: compiler.c
	$(CC) -c compiler.c

clean:
	rm -rf *o compiler