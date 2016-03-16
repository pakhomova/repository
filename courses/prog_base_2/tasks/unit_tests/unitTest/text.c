#include "text.h"
#include <string.h>
#include <stdlib.h>

struct text_s {
    int count;
    char sentence[N][L];
    int format[N];
};

text_t *text_new (void) {
    text_t *text_new = malloc(sizeof(struct text_s));
    text_new->count = 0;
    return text_new;
}

void text_free (text_t *self) {
    free (self);
}

int text_getCount (text_t *self) {
    return self->count;
}

int text_getFormat (text_t *self, int place) {
    return self->format[place];
}

char* text_getString (text_t *self, int place) {
    return self->sentence[place];
}

void text_insert (text_t *self, int place, char *sentence, int format) {
    int i, n = self->count;
    for (i = n - 1; i >= place; i--) {
        strcpy (self->sentence[i+1], self->sentence[i]);
        self->format[i+1] = self->format[i];
    }
    strcpy (self->sentence[place], sentence);
    self->format[place] = format;
    self->count++;
}

void text_delete (text_t *self, int place) {
    int i, n = self->count;
    for (i = place; i < n - 1; i++) {
        strcpy (self->sentence[i], self->sentence[i+1]);
        self->format[i] = self->format[i+1];
    }
    self->count--;
}

text_t *text_writeFormat (text_t *self, int format) {
    text_t *text = text_new();
    int i, k = 0;
    for (i = 0; i < self->count; i++)
        if (self->format[i] == format) {
            text_insert (text, k, self->sentence[i], self->format[i]);
            k++;
        }
    return text;
}



