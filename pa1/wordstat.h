#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct WORDNODE{
	char *word;
	int count;
	struct WORDNODE *next;
};

typedef struct WORDNODE WORDNODE;

void printPalindromes(char *, short);
int getLineCount(char *);
int getWordCount(char *);
WORDNODE *generatePalindromeLinkedList(char *, int );
void printLinkedListWithCounts(WORDNODE *);
void printLinkedList(WORDNODE *);
void fillArrayWithFileChars(char *, char *);
int getNumberOfCharsInFile(char *);
short int isPalindrome(char *);
WORDNODE *putInLinkedList(WORDNODE *, char *);
