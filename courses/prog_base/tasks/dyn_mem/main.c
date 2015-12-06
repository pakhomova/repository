#include <stdio.h>
#include <stdlib.h>

int main(void){
int k = 0;
printf("Please, enter your string: ");
char * str1 = (char *) malloc(50);
if (str1==NULL){
    exit (1);
    }
char * str2 = (char *) malloc(7);
if (str2==NULL){
    exit (1);
    }
str2 = "eyuioa";
char * res = (char *) malloc(50);
if (res==NULL){
    exit (1);
    }
scanf("%s", str1);
res = strpbrk(str1, str2);
while (res != NULL){
    k++;
    res = strpbrk (res+1,str2);
    }
printf("Number of vowel is %i.", k);
free(str1);
free(str2);
free(res);
return 0;
}
