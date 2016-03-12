#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#define N 100
#define L 30

typedef struct text_s text_t;

text_t *text_new (void);
void text_free (text_t *self);

int text_getCount (text_t *self);
int text_getFormat (text_t *self, int place);
char* text_getString (text_t *self, int place);

void text_insert (text_t *self, int place, char *sentence, int format);
void text_delete (text_t *self, int place);
void text_writeFormat (text_t *self, int format);

#endif


