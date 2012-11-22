//4294967295
#include "common.h"

char * convertDecToHex(lu x){
	int j;
	char *hex = (char *)calloc(9, sizeof(char));
	hex[8] = '\0';
	for (j = 0; j < 7; j++){
		hex[j] = ' ';
	}	
	int rem;
	int i = 7;
	while (x > 0){
		rem = x - (x/16)*16;
		char remC;
		if (rem >= 10) remC = rem + 55;
		else remC = rem + 48; //converts to a letter or number, using ascii value
		hex[i] = remC;
		i--;
		x = x/16;
	}
	return (char *)removeLeadingSpaces(hex);
}

char * convertDecToOct(lu x){
	int j;
	char *oct = (char *)calloc(12, sizeof(char));
	oct[11] = '\0';
	for (j = 0; j < 10; j++){
		oct[j] = ' ';
	}	
	int rem;
	int i = 10;
	while (x > 0){
		rem = x - (x/8)*8;
		char remC;
		remC = rem + 48;
		oct[i] = remC;
		i--;
		x = x/8;
	}
	return (char *)removeLeadingSpaces(oct);
}

char * convertDecToBin(lu x){
	int j;
	char *bin = (char *)calloc(33, sizeof(char));
	bin[32] = '\0';
	for (j = 0; j < 31; j++){
		bin[j] = ' ';
	}	
	int rem;
	int i = 31;
	while (x > 0){
		if (x % 2  == 1) bin[i] = '1';
		else bin[i] = '0';
		i--;
		x = x/2;
	}
	return (char *)removeLeadingSpaces(bin);
}

lu convertBinToDec(char *bin){
	lu dec = 0;
	char c;
	int i;
	int n = strlen(bin);
	for( i = 0; i < n; i++){
		c = bin[i];
		if ( c == '1' ) {
			dec = dec + pow(2, n-i-1);
		}
	}
	return dec;
}

lu convertHexToDec(char* hex){
	lu dec = 0;
	int i;
	int n = strlen(hex);
	char c;
	for (i = 0; i < n; i++){
		c = hex[i];
		if (c >= 48 && c <= 57)
			dec += (c - 48)*pow(16, n - i - 1); //depends on ascii value
		else if ( c >= 65 && c <= 70)
			dec += (c - 55)*pow(16, n - i - 1);
		else return -1;
	}
	return dec;
}

lu convertOctToDec(char* oct){
	lu dec = 0;
	int i;
	int n = strlen(oct);
	char c;
	for (i = 0; i < n; i++){
		c = oct[i];
		if (c >= 48 && c <= 55)
			dec += (c - 48)*pow(8, n - i - 1);
		else return -1;
	}
	return dec;
}

char * removeLeadingSpaces(char* num){
	int n = strlen(num);
	int i;
	for (i = 0; i < n; i++){
		if (num[i] != ' ') return (num + i);
	}
	
	return (char *)NULL;
}
