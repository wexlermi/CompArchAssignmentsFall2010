#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#define MAX 4294967295ul

typedef unsigned long int lu;

char * convertDecToHex(lu);
char * convertDecToBin(lu);
char * convertDecToOct(lu);
lu convertBinToDec(char*);
lu convertHexToDec(char*);
lu convertOctToDec(char*);
char * removeLeadingSpaces(char*);
