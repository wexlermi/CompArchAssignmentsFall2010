CC=gcc
CCFLAGS = -ansi -pedantic -Wall

all: fibonacci

fibonacci: fibonacci.c fibonacci.h fib.h fib.s
	$(CC) $(CCFLAGS) -o fibonacci fibonacci.c fib.s
	
clean:
	rm fibonacci
