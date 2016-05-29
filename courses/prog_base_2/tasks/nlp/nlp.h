#ifndef NLP_H
#define NLP_H

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef struct word_s word_t;

word_t *word_new (char *str);
word_t *word_copy (word_t *word);
int word_size (word_t *word);
void word_print (word_t *word, FILE *file);
void word_free (word_t *word);
void word_free_func (void *word);

typedef struct sentence_s sentence_t;

sentence_t *sentence_new (list_t *words);
sentence_t *sentence_create ();
void sentence_add (sentence_t *sentence, word_t *word);
void sentence_print(sentence_t *sentence, FILE *file);
void sentence_free (sentence_t *sentence);
void sentence_free_func (void *sentence);
list_t *sentence_words(sentence_t *sentence);

typedef struct text_s text_t;

text_t *text_new (list_t *sentences);
text_t *text_create ();
void text_print (text_t *text, FILE *file);
void text_free (text_t *text);
list_t *text_sentences(text_t *text);
void text_add (text_t *text, sentence_t *sentence);
int text_find (text_t *text, char *word);

#endif // NLP_H
