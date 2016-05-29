#include "nlp.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct word_s {
    char *str;
};

word_t *word_new (char *str) {
    word_t *word = malloc(sizeof(word_t));
    word->str = malloc((strlen(str) + 1) * sizeof(char));
    strcpy (word->str, str);
    return word;
}

int word_size (word_t *word) {
    return strlen(word->str);
}

void word_print (word_t *word, FILE *file) {
    fprintf (file, "%s", word->str);
}

void word_free (word_t *word) {
    free (word->str);
    free (word);
}

void word_free_func (void *word) {
    word_free (word);
}

word_t *word_copy (word_t *word) {
    word_t *w = word_new(word->str);
    return w;
}

struct sentence_s {
    list_t *words;
};

sentence_t *sentence_new (list_t *words) {
    sentence_t *sentence = sentence_create();
    int i;
    for (i = 0; i < list_size(words); i++)
        sentence_add (sentence, list_get(words, i));
    return sentence;
}

sentence_t *sentence_create () {
     sentence_t *sentence = malloc(sizeof(sentence_t));
     sentence->words = list_new(word_free_func);
     return sentence;
}

sentence_t *sentence_copy (sentence_t *sentence) {
    sentence_t *sen = sentence_new(sentence->words);
    return sen;
}

list_t *sentence_words(sentence_t *sentence) {
    return sentence->words;
}

void sentence_add (sentence_t *sentence, word_t *word) {
    list_push (sentence->words, word_copy(word));
}

void sentence_print(sentence_t *sentence, FILE *file) {
    int i;
    for (i = 0; i < list_size(sentence->words); i++) {
        word_print (list_get(sentence->words, i), file);
        if (i != list_size(sentence->words) - 1)
            fprintf(file, " ");
    }
}

int sentence_find (sentence_t *sentence, char *word) {
    int ans = 0, i;
    for (i = 0; i < list_size(sentence->words); i++) {
        word_t *w = word_copy(list_get(sentence->words, i));
        if (strcmp(w->str, word) == 0) ans++;
        word_free (w);
    }
    return ans;
}

void sentence_free (sentence_t *sentence) {
    list_free (sentence->words);
    free (sentence);
}

void sentence_free_func (void *sentence) {
    sentence_free (sentence);
}

struct text_s {
    list_t *sentences;
};

text_t *text_new (list_t *sentences) {
    text_t *text = text_create();
    int i;
    for (i = 0; i < list_size(sentences); i++)
        text_add (text, list_get(sentences, i));
    return text;
}

text_t *text_create () {
    text_t *text = malloc(sizeof(text_t));
    text->sentences = list_new(sentence_free_func);
    return text;
}

void text_print (text_t *text, FILE *file) {
    int i;
    for (i = 0; i < list_size(text->sentences); i++) {
        sentence_print (list_get(text->sentences, i), file);
        fprintf (file, "\n");
    }
}

int text_find (text_t *text, char *word) {
    int ans = 0, i;
    for (i = 0; i < list_size(text->sentences); i++)
        ans += sentence_find (list_get(text->sentences, i), word);
    return ans;
}

void text_add (text_t *text, sentence_t *sentence) {
    list_push (text->sentences, sentence_copy(sentence));
}

void text_free (text_t *text) {
    list_free (text->sentences);
    free(text);
}
