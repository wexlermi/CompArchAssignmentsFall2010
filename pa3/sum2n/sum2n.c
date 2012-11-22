#include "sumInts.h"
#include "sum2n.h"

int main(int argc, char *argv[]){
	int n, k, result;
	
	if (argc == 2){
		if (!strcmp(argv[1], "-h"))
			printf("Usage: sum2n <positive integer> <positive integer>\n");
	}
	else if (argc == 3){
		n = atoi(argv[1]);
		k = atoi(argv[2]);
		result = sumInts(n, k);
		if ( result != -1 )
			printf("%d\n", result);
		else {
			printf("overflow\n");
			return 1;
		}
		
		return 0;
	}
	
	return 1;
}
