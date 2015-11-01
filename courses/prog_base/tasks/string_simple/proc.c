#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * process (char * resultStr, const char * textLines[], int linesNum, const char * extraStr) {
    int i,amount = 0;
    char s[100];
    for (i=0; i<linesNum; i++) {
        int k=0,j;
        for (j=0; j<strlen(extraStr); j++)
        if (strchr(textLines[i],extraStr[j])!=NULL) {
            k=1;
            break;
        }
        if (k==1) {
            if (amount!=0) strcat (s,", ");
            amount++;
            if (amount==1) strcpy(s,textLines[i]); else strcat (s,textLines[i]);
        }
    }
    if (amount==0) strcpy (resultStr,"0 NULL"); else {
        itoa (amount,resultStr,10);
        strcat (resultStr," ");
        strcat (resultStr,s);
    }
    return resultStr;
}
