#include <stdio.h>
#include "text.h"

int main () {
    FILE *input;
    input = fopen ("input.txt","r");

    text_t *text;
    text = text_new();

    int stringCount, i, format;
    char string[L];
    fscanf (input, "%i", &stringCount);

    for (i = 0; i < stringCount; i++) {
        fscanf (input, "%i", &format);
        fscanf (input, "%s", string);
        text_insert(text, i, string, format);
    }

    text_delete (text, 3);

    printf ("%i\n", text_getCount(text));
    text_writeFormat (text, 0);

    text_free (text);

    fclose (input);
    return 0;
}

