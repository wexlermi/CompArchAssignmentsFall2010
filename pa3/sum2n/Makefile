CC=gcc
CCFLAGS = -ansi -pedantic -Wall

all: sum2n

sum2n: sum2n.c sum2n.h sumInts.s sumInts.h
	$(CC) $(CCFLAGS) -o sum2n sum2n.c sumInts.s
	
clean:
	rm sum2n
