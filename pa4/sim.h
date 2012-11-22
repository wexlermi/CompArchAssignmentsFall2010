#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define CACHE_SIZE 16384
#define BLOCK_SIZE 4
#define ADDRESS_SIZE 32

typedef unsigned int lu;

typedef struct TUPLE{
	lu block;
	int tag;
	int valid;
	int dirty;
} TUPLE;


TUPLE cache[CACHE_SIZE/BLOCK_SIZE];

int cache_hits;
int cache_misses;
int mem_reads;
int mem_writes;

int numSets;
int setIndexBits;
int blockOffsetBits;
int addressBits;
int tagBits;

void read(lu);
void write(lu);

int writeBackMode;

int strcmp(const char*, const char*);
double log2(double);
