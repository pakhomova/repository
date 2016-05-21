#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "stack.h"

#define ITER 40

void aa (char *s) {
    printf ("Subscriber 1: %s\n", s);
}

void bb (char *s) {
    printf ("Subscriber 2: %s\n", s);
}

void enter (stack_t *stack) {
    int x = rand() % 101 - 50;
    printf ("%d\n", x);
    if (x > 0) stack_push (stack, x);
        else stack_pop (stack);
}

//функции юнит-тестов

static void new_void_zeroCount(void **state)
{
    stack_t *stack = stack_new();
    assert_int_equal(stack_getCount(stack), 0);
    stack_free(stack);
}

static void push_oneElement_countOne(void **state)
{
    stack_t *stack = stack_new();
    stack_push (stack, 5);
    assert_int_equal (stack_getCount(stack), 1);
    stack_free(stack);
}

static void pop_hasOnePushedElement_CountZero(void **state)
{
    stack_t *stack = stack_new();
    stack_push (stack, 5);
    stack_pop (stack);
    assert_int_equal(stack_getCount(stack), 0);
    stack_free(stack);
}

static void pop_hasTwoPushedElement_ZeroElementCountOne(void **state)
{
    stack_t *stack = stack_new();
    stack_push (stack, 5);
    stack_push (stack, 3);
    stack_pop (stack);
    assert_int_equal(stack_getCount(stack), 1);
    assert_int_equal(stack_peek(stack), 5);
    stack_free(stack);
}

static void push_twoElement_countTwoLastPushedElementOnTop(void **state)
{
    stack_t *stack = stack_new();
    stack_push (stack, 5);
    stack_push (stack, 3);
    assert_int_equal (stack_getCount(stack), 2);
    assert_int_equal (stack_peek(stack), 3);
    stack_free(stack);
}

int main () {


       const struct CMUnitTest tests[] =
    {
        cmocka_unit_test (new_void_zeroCount),
        cmocka_unit_test (push_oneElement_countOne),
        cmocka_unit_test (pop_hasOnePushedElement_CountZero),
        cmocka_unit_test (pop_hasTwoPushedElement_ZeroElementCountOne),
        cmocka_unit_test (push_twoElement_countTwoLastPushedElementOnTop)
    };



    stack_t *stack1 = stack_new();
    stack_t *stack2 = stack_new();

    stack_subsEventOverFlow (stack1, stack2, stack_cb1); //подписываем стек 2 на стек 1 функцией, которая отвечает за переполнение
    stack_subsEventOverFlow (stack2, stack1, stack_cb1);
    stack_subsEventUnderFlow (stack1, stack2, stack_cb2);
    stack_subsEventUnderFlow (stack2, stack1, stack_cb2);

    //для мультиподписок
    stack_addOver (stack1, aa);
    stack_addOver (stack2, aa);

    stack_addOver (stack1, bb);
    stack_addOver (stack2, bb);

    stack_addUnder (stack1, aa);
    stack_addUnder (stack1, bb);

    stack_addUnder (stack2, aa);
    stack_addUnder (stack2, bb);

    srand(time(NULL));
    int i;
    for (i = 0; i < ITER; i++) {
        printf ("Iteration %d:\n", i + 1);
        if (rand() % 2 == 0) {
            printf ("Stack 1\n");
            enter (stack1);
        }
        else {
            printf ("Stack 2\n");
            enter (stack2);
        }
        stack_print (stack1);
        stack_print (stack2);
        printf ("\n");
    }


    stack_free (stack1);
    stack_free (stack2);
    return cmocka_run_group_tests(tests, NULL, NULL);
    return 0;
}
