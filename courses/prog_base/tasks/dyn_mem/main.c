#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	char * inputStr 	= NULL;
	char * vowelCharPtr = NULL;
	char * vowels 		= "eyuioaEYUIOA";
	int  * count 		= NULL;
	inputStr = (char *) malloc(50 * sizeof(char));
	count 	 = (int  *) malloc( 1 * sizeof(int ));
	if (NULL == inputStr || NULL == count){
		printf("Alloc error");
		exit(1);
	}
	*count = 0;
	printf("Please, enter your string: ");
	scanf("%s", inputStr);
	vowelCharPtr = strpbrk(inputStr, vowels);
	while (NULL != vowelCharPtr) {
		(*count) ++;
		vowelCharPtr = strpbrk(vowelCharPtr + 1, vowels);
	}
	printf("Number of vowels is %i.", *count);
	free(inputStr);
	free(count);
	return 0;
}
