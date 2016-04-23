#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define LENSTR 30
#define MAXSIZE 15

typedef struct stack_s stack_t;

stack_t * stack_new(void);
void stack_free(stack_t * self);

int stack_getCount(stack_t * self);

void stack_push(stack_t * self, char *val);
char *stack_pop(stack_t * self);
char *stack_peek(stack_t * self);

void stack_print(stack_t * self);

#endif // STACK_H_INCLUDED
