#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

#define SIZE 10
#define SUBS 10

typedef struct event_s {
    void *observer;  //атд-наблюдатель
    void *callback;  //коллбек - функция
} event_t;

struct stack_s {
    int count;
    int arr[SIZE];

    event_t eventOverFlow;
    event_t eventUnderFlow;

    int over_amount;  //колличество подписчиков на одновременное переполнение
    stack_event callbacks_over[SUBS];  //массив указателей на функции-подписчики для переполнения
    int under_amount;
    stack_event callbacks_under[SUBS];
};

int stack_getCount(stack_t *stack) {
return stack->count;
}

int stack_peek(stack_t *stack) {
return stack->arr[stack->count-1];
}

void stack_cb1 (stack_t *stack, int element) {
    if (stack->count == SIZE) {    //если стек-подписчик полный
        int i = 0;
        while (i < stack->over_amount) {    //проходимся по массиву мультиподписчиков-коллбеков
            stack_event se = stack->callbacks_over[i];
            se ("OVERFLOW");
            i++;
        }
        return;
    }
    stack_push (stack, element);
}

int stack_cb2 (stack_t *stack) {
    if (stack->count == 0) {
        int i = 0;
        while (i < stack->under_amount) {
            stack_event se = stack->callbacks_under[i];
            se ("UNDERRFLOW");
            i++;
        }
        return 0;
    }
    return stack_pop(stack);
}

void stack_addOver (stack_t *self, stack_event ev) {  //заносим указатели на коллбеки в динамический список подписчиков(для мультиподписки)
    self->over_amount++;
    self->callbacks_over[self->over_amount - 1] = ev;
}

void stack_addUnder (stack_t *self, stack_event ev) {
    self->under_amount++;
    self->callbacks_under[self->under_amount - 1] = ev;
}

stack_t *stack_new () {
    stack_t *self = malloc(sizeof(struct stack_s));
    self->count = 0;
    self->under_amount = 0;
    self->over_amount = 0;
    return self;
}

void stack_free (stack_t *self) {
    free(self);
}

void stack_subsEventOverFlow (stack_t *self, stack_t *observer, event1_fn callback) {  //функция, которая подписывает
    (self->eventOverFlow).observer = observer;
    (self->eventOverFlow).callback = callback;
}

void stack_subsEventUnderFlow (stack_t *self, stack_t *observer, event2_fn callback) {
    (self->eventUnderFlow).observer = observer;
    (self->eventUnderFlow).callback = callback;
}

void stack_push (stack_t *self, int element) {
    if (self->count == SIZE) {
        event1_fn cb = (event1_fn)(self->eventOverFlow).callback;
        cb ((stack_t *)(self->eventOverFlow).observer, element);
        return;
    }
    self->count++;
    self->arr[self->count - 1] = element;
}

int stack_pop (stack_t *self) {
    if (self->count == 0) {
        event2_fn cb = (event2_fn)(self->eventUnderFlow).callback;
        return cb ((stack_t *)(self->eventUnderFlow).observer);
    }
    self->count--;
    int ret = self->arr[self->count];
    return ret;
}

void stack_print (stack_t *self) {
    if (self->count == 0) {
        printf ("Empty stack\n");
        return;
    }
    int i;
    for (i = 0; i < self->count - 1; i++)
        printf ("%d ", self->arr[i]);
    printf ("%d\n", self->arr[self->count - 1]);
}
