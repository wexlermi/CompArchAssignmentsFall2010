#include "fib.h"
#include "fibonacci.h"
int main(int argc, char *argv[]){
	int num;
	int result;

	if (argc == 2){
		
		if (!strcmp(argv[1], "-h")){
			printf("Usage: fibonacci <positive integer >\n");
			return 0;
		}
		
		num = atoi(argv[1]);
		result = fib(num);
		if (result != -1)
			printf("%d\n", result);
		else{	
			printf("overflow\n");
			return 1;
		}
		return 0;
	}
	
	return 1;
}
