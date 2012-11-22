#include "common.h"

int main(int argc, char *argv[]){
	char *a = (char *)(argv[1]);
	char *b = (char *)(argv[2]);
	char *base1 = (char *)(argv[3]);
	char *base2 = (char *)(argv[4]);
	char *outputBase = (char *)(argv[5]);
	
	lu x, y;
	
	if ( !strcmp(base1, "dec") ) x = strtoul(a, NULL, 10);
	else if ( !strcmp(base1, "hex") ) x = convertHexToDec(a);
	else if ( !strcmp(base1, "bin") ) x = convertBinToDec(a);
	else if ( !strcmp(base1, "oct") ) x = convertOctToDec(a);
	
	if ( !strcmp(base2, "dec") ) y = strtoul(b, NULL, 10);
	else if ( !strcmp(base2, "hex") ) y = convertHexToDec(b);
	else if ( !strcmp(base2, "bin") ) y = convertBinToDec(b);
	else if ( !strcmp(base2, "oct") ) y = convertOctToDec(b);
	
	if ( y > MAX - x){
		printf("overflow\n");
		return 1;
	}
	
	lu result = x + y;
	char *output;
	
	
	if (!strcmp(outputBase, "hex"))
		output = convertDecToHex(result);
	else if (!strcmp(outputBase, "bin"))
		output = convertDecToBin(result);
	else if (!strcmp(outputBase, "oct"))
		output = convertDecToOct(result);
	else{
		printf("%lu\n", result);
		return 0;
	}
		
	printf("%s\n", output);
	return 0;
	
}
