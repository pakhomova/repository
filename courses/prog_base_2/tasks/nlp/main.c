#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "nlp.h"

char *stradd (char *str, char c) {
    int n = strlen(str) + 2;
    char *w = malloc (n * sizeof(char));
    strcpy (w, str);
    w[n - 2] = c;
    w[n - 1] = '\0';
    return w;
}

char *strnew () {
    char *str = malloc(1);
    *str = '\0';
    return str;
}

int main (){
    FILE *input;
    input = fopen("text.txt", "r");

    char *str = strnew();

    sentence_t *currSentence = sentence_create();
    text_t *text = text_create();

    while (1) {
        char c = fgetc(input);
        if (c == EOF || isspace(c) || c == ',' || c == '.' || c == '!' || c == '?' || c == ';') {
            if (strlen(str) != 0) {
                word_t *word = word_new(str);
                sentence_add(currSentence, word);
                free (str);
                word_free (word);
                str = strnew();
            }
        }
        if (c == EOF || c == '.' || c == '!' || c == '?') {
            text_add (text, currSentence);
            sentence_free(currSentence);
            currSentence = sentence_create();
        }
        if (c == EOF) break;
        if (isalpha(c)) {
            c = tolower(c);
            char *w = stradd(str, c);
            free (str);
            str = w;
        }
    }
    fclose (input);
    FILE *output;
    output = fopen("result.txt", "w");
    input = fopen ("stopwords.txt", "r");

    int stopCount, i;
    fscanf (input, "%d", &stopCount);
    for (i = 0; i < stopCount; i++) {
        char s[15];
        fscanf (input, "%s", s);
        fprintf (output, "%s: %d\n", s, text_find (text, s));
    }

    fclose (input);
    fclose (output);
    free (str);
    sentence_free(currSentence);
    text_free(text);
    return 0;
}
