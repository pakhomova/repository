#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "stack.h"

typedef int (*cmp_f)(stack_t *a);
typedef int (*react_f)(stack_t * a, int b);

typedef struct dynamic_s {
    HANDLE hLib;
    cmp_f cmp;
    react_f react;
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);

const char * userChoice();

int main(void) {
    stack_t *stack = stack_new();

    char *str = malloc(LENSTR * sizeof(char));

    while (stack_getCount(stack) < MAXSIZE) {
        gets (str);
        stack_push (stack, str);
    }

    const char *dllName = userChoice();
    dynamic_t * dll = dynamic_init(dllName);

    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->cmp) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->react) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!\n");

    int comp = dll->cmp(stack);

    int err = dll->react (stack, comp);

    if (err == -1) printf ("Error\n");
        else stack_print (stack);

    dynamic_clean (dll);
    free (str);
    stack_free (stack);
    return 0;
}

const char * userChoice() {
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2) {
        printf("Choose DLL to load:\n1. lib1Lab2DLL\n2. lib2Lab2DLL\n> ");
        scanf("%i", &dllNum);
        if (dllNum == 1) {
            return "lib1Lab2DLL.dll";
        } else if (dllNum == 2) {
            return "lib2Lab2DLL.dll";
        }
    }
    return NULL;
}

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->cmp = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib) {
        dyn->cmp = (cmp_f)GetProcAddress(dyn->hLib, "compare");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}
