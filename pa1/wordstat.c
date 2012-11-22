#include "wordstat.h"

int main(int argc, char *argv[]){

	char *option;
	char *fileName;
	FILE *fp;
	
	if (argc < 3){
		 printf("Incorrect arguments entered.\n");
		 return 1;
	}

	option = argv[1];
	fileName = argv[2];
	
	fp = fopen(fileName, "r");
	
	if (fp == NULL){
		printf("Input file does not exist.\n");
		return 1;
	}
	fclose(fp);
	
	/*!strcmp looks for string equality*/
	if (!strcmp(option, "-l")) 
		printf("%d\n", getLineCount(fileName));
	else if (!strcmp(option, "-w"))
		printf("%d\n", getWordCount(fileName));
	else if (!strcmp(option, "-pf"))
		printPalindromes(fileName, 1);
	else if (!strcmp(option, "-p"))
		printPalindromes(fileName, 0);
	else if (!strcmp(option, "-h")){
		printf("Usage: ./wordstat <option> <filename>\nOptions:\n-l : number of lines\n");
		printf("-w: number of words\n-p: palindrome’s statistics\n-pf: palindrome's frequency\n");
	}
	
	return 0;
}

int getLineCount(char *fileName){
	FILE *fp = fopen(fileName, "r");
	
	char line[128];
	int lineCount = 0;

	while ( fgets( line, sizeof(line), fp) != NULL ){
		lineCount++;
	}
	fclose(fp);
	return lineCount;
}

int getWordCount(char *fileName){
	FILE *fp = fopen(fileName, "r");
	
	char c;
	int wordCount = 0;
	short readingWord = 0;
	while ( (c  = fgetc(fp)) != EOF){
		if (isalpha(c)){
			if (!readingWord){
				readingWord = 1;
				wordCount++;
			}
		}
		else if (readingWord) readingWord = 0;
	}
	fclose(fp);
	
	
	
	return wordCount;

}

void printPalindromes(char *fileName, short withCount){
	WORDNODE *head;
	int numChars = 	getNumberOfCharsInFile(fileName);
	
	char *fileChars = (char *)(malloc(numChars*sizeof(char)));
	
	fillArrayWithFileChars(fileChars, fileName);
	
	head = generatePalindromeLinkedList(fileChars, numChars);
	
	if (withCount) printLinkedListWithCounts(head);
	else printLinkedList(head);
}

WORDNODE *generatePalindromeLinkedList(char *fileChars, int numChars){
	short readingWord;
	char c;
	int wordStart;
	int wordEnd;
	char *currWord;
	int i;
	
	WORDNODE *head = (WORDNODE *) malloc(sizeof(WORDNODE));
	head->count = 0; /*initialize first node to count 0*/
	
	readingWord = 0;

	

	for (i = 0; i < numChars; i++){
		c = fileChars[i];
		
		if (isalpha(c)){
			if (!readingWord){
				readingWord = 1;
				wordStart  = i;
			}
		}
		else if (readingWord) {
			int j;
			
			readingWord = 0;
			wordEnd = i - 1;
			
			currWord = (char *)malloc( (wordEnd - wordStart + 2)*sizeof(char) );
			
			
			for (j = 0; j < wordEnd - wordStart + 1; j++ ){
				currWord[j] = toupper(fileChars[wordStart + j]); /*copies current word into memory*/
			}
			currWord[wordEnd - wordStart + 1] = '\0';
			
		
			if (isPalindrome(currWord))
				head = putInLinkedList(head, currWord);
			else
				free(currWord);
			
		}
	}
	
	return head;
	
	
	
}

void printLinkedList(WORDNODE *head){
	WORDNODE *ptr;
	ptr = head;
	while (ptr->count != -1){
		printf( "%s\n", ptr->word );
		ptr = ptr->next;
	}
}

void printLinkedListWithCounts(WORDNODE *head){
	WORDNODE *ptr;
	ptr = head;
	while (ptr->count != -1){
		printf( "%s\t%d\n", ptr->word, ptr->count );
		ptr = ptr->next;
	}
}

void fillArrayWithFileChars(char *fileChars, char *fileName){
	FILE *fp = fopen( fileName, "r");
	
	char c;
	int i = 0;
	while ( (c = getc(fp)) != EOF){
		*(fileChars + i) = c;
		i++;
	}
	fclose(fp);
}


int getNumberOfCharsInFile(char *fileName){
	FILE *fp = fopen(fileName, "r");
	int count = 0;
	while (getc(fp) != EOF) count++;
	fclose(fp);
	return count;
}

short isPalindrome(char *word){
	int wordSize;
	char *newWord;
	int i;
	
	wordSize = strlen(word);
	newWord = (char *)malloc((wordSize + 1)*sizeof(char));
	
	for( i = wordSize - 1; i >=0; i--){
		newWord[wordSize - i - 1] = word[i];
	}
	newWord[wordSize] = '\0';
	
	return !strcmp(word, newWord);
}

WORDNODE *putInLinkedList(WORDNODE *head, char *word){
	WORDNODE *nullNode;
	WORDNODE *prev;
	WORDNODE *ptr;
	int stringComp;
	
	if (head->count == 0){
		head->word = word;
		head->count = 1;
		
		nullNode = (WORDNODE *)malloc(sizeof(WORDNODE));
		nullNode->count = -1;
		head->next = nullNode;
		
		return head;
	}
	

	
	ptr = head;
	
	while (1){
		stringComp = strcmp(word, ptr->word);
		if ( stringComp == 0){
			(ptr->count)++; /*increment count for duplicate palindromes*/
			break;
		}
		else {
			if( stringComp > 0 &&  ptr->next->count != -1){/*if not at end of list, and this word is greater than current word*/
				prev = ptr; 
				ptr = ptr->next;
			}
			else {
				WORDNODE *newNode = (WORDNODE *) malloc(sizeof(WORDNODE)); 
				newNode->word = word;
				newNode->count = 1;
				if( stringComp < 0){/*if word is less than in the alphabet than current word*/
					if (!strcmp(ptr->word, head->word)) /*if we are at the first word in list*/
						head = newNode;
					else
						prev->next = newNode;
					newNode->next = ptr;	
				}
				else { /*we are at the end of the list*/
					newNode->next = ptr->next;
					ptr->next = newNode;
				}			
				break;
			}
		}
			
	} 
	
	return head;
}




