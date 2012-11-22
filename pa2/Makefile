CC=gcc
CCFLAGS = -ansi -pedantic -Wall

all:
	$(CC) -o add  add.c common.c -lm
	$(CC) -o sub  sub.c common.c -lm
	$(CC) -o mult  mult.c common.c -lm

clean: 
	rm add
	rm sub
	rm mult
