#include "sim.h"


int main(int argc, char* argv[]){
	
	char* mode;
	char* fileName;
	FILE *fp;
	
	
	char* instructionAddress;
	
	char readOrWrite;
	lu address;
	
	
	
	if (argc != 2 && argc != 3){
		printf("Invalid arguments\n");
		return 1;
	}
	
	if( argc == 2){
		if (!strcmp("-h", argv[1])){
			printf("Usage:\nsim [-h] <write policy> <trace file>\n");
			return 0;
		}
		else{
			printf("Invalid arguments\n");
			return 1;
		}
	}
	
	mode = argv[1];
	fileName = argv[2];
	
	if(!strcmp(mode, "wb"))
		writeBackMode = 1;
	else if (strcmp(mode, "wt")){
		printf("Invalid arguments\n");
		return 1;
	}
		
	
	numSets = CACHE_SIZE/BLOCK_SIZE;
	setIndexBits = log2(numSets);
	blockOffsetBits = log2(BLOCK_SIZE);
	tagBits = ADDRESS_SIZE - (setIndexBits + blockOffsetBits);
	
	
	
	fp = fopen(fileName, "r");
	
	if(fp == NULL){
		printf("File does not exist\n");
		return 1;	
	}
	
	
	instructionAddress = (char *)malloc(32 * sizeof(char));

	
	while(fscanf(fp, "%s %c %x", instructionAddress, &readOrWrite, &address) == 3){
		instructionAddress = (char *)malloc(ADDRESS_SIZE*sizeof(char));
		if (readOrWrite == 'R')
			read(address);
		else
			write(address);
	}
	
	fclose(fp);
	printf("CACHE HITS: %d\n", cache_hits);
	printf("CACHE MISSES: %d\n", cache_misses);
	printf("MEMORY R (READ): %d\n", mem_reads);
	printf("MEMORY W (WRITE): %d\n", mem_writes);

	return 0;
	
}

void read(lu address){
	int setIndex = address<<tagBits>>(blockOffsetBits+ tagBits);
	int tag = address>>(blockOffsetBits + setIndexBits);
	int block = address<<(tagBits+blockOffsetBits+setIndexBits);
	
	if (writeBackMode){
		if (cache[setIndex].valid){
			if( tag == cache[setIndex].tag )
				cache_hits++;
			else{
				mem_reads++;
				cache_misses++;
				if(cache[setIndex].dirty){
					mem_writes++;
					cache[setIndex].dirty = 0;
				}
				cache[setIndex].block = block;
				cache[setIndex].tag = tag;
			}
		}
		else{
			mem_reads++;
			cache_misses++;
			cache[setIndex].block = block;
			cache[setIndex].valid = 1;
			cache[setIndex].tag = tag;
		}
	}
	else{
		if (cache[setIndex].valid && tag == cache[setIndex].tag){
			cache_hits++;
		}
		else{
			cache_misses++;
			cache[setIndex].block = block;
			cache[setIndex].valid = 1;
			cache[setIndex].tag = tag;
			mem_reads++;
		}
	}
}

void write(lu address){
	int setIndex = address<<tagBits>>(blockOffsetBits+ tagBits);
	int tag = address>>(blockOffsetBits + setIndexBits);
	int block = address<<(tagBits+blockOffsetBits+setIndexBits);
	
	if (writeBackMode){
		if (cache[setIndex].valid){
			if( tag == cache[setIndex].tag ){
				cache_hits++;
				cache[setIndex].dirty = 1;
			}
			else{
				mem_reads++;
				cache_misses++;
				if(cache[setIndex].dirty){
					mem_writes++;
				}
				cache[setIndex].dirty = 1;
				cache[setIndex].block = block;
				cache[setIndex].tag = tag;
			}
		}
		else{
			mem_reads++;
			cache_misses++;
			cache[setIndex].block = block;
			cache[setIndex].valid = 1;
			cache[setIndex].tag = tag;
			cache[setIndex].dirty = 1;
		}
	}
	else{		if (cache[setIndex].valid && tag == cache[setIndex].tag){
			cache_hits++;
		}
		else{
			cache_misses++;
			cache[setIndex].block = block;
			cache[setIndex].valid = 1;
			cache[setIndex].tag = tag;
			mem_reads++;
		}
		mem_writes++;
	}
}
