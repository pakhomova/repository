#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct stack_s {
    char *array[MAXSIZE];
    int count;
};

stack_t * stack_new(void) {
    stack_t * s = malloc(sizeof(struct stack_s));
    s->count = 0;
    return s;
}

void stack_free(stack_t * self) {
    while (stack_pop(self) != NULL ) {}
    free(self);
}

int stack_getCount(stack_t * self) {
    return self->count;
}

void stack_push(stack_t * self, char *val) {
    self->array[self->count] = malloc (LENSTR * sizeof(char));
    strcpy(self->array[self->count], val);
    self->count += 1;
}

char *stack_pop(stack_t * self) {
    if (self->count > 0) {
        char *val = malloc(LENSTR * sizeof(char));
        strcpy (val, self->array[self->count - 1]);
        free (self->array[self->count - 1]);
        self->count -= 1;
        return val;
    }
    return NULL;
}

char *stack_peek(stack_t * self) {
    if (self->count > 0) {
        char *val = malloc(LENSTR * sizeof(char));
        strcpy (val, self->array[self->count - 1]);
        return val;
    }
    return NULL;
}

void stack_print(stack_t * self) {
    for(int i = 0; i < self->count; i++) {
        printf("%s\n", self->array[i]);
    }
}
