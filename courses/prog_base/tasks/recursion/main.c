#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int check(char string[], int k){
    if(k==strlen(string)){
        return 0;
    }
    if(isspace(string[k])){
        return check(string,k+1)+1;
    }
    return check(string,k+1);
}

int main(void){
    char string[30];
    printf("Please, enter the string:\n");
    fflush(stdin);
    fgets(string, sizeof(string), stdin);
    printf("Amount of spaces is: %i\n",check(string,0)-1);
    return 0;
}
