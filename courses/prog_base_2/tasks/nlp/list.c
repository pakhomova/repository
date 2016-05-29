#include "list.h"

#include <stdlib.h>
#include <string.h>

struct list_s {
    list_free_func_t free_func;
    void **elems; //массив указателей на войд
    int size;
};

list_t *list_new (list_free_func_t free_func) {
    list_t *list = malloc(sizeof(list_t));
    list->free_func = free_func;
    list->elems = malloc(0 * sizeof(void *));
    list->size = 0;
    return list;
}

void *list_get (list_t *list, int index) {
    if (index < list->size)
        return list->elems[index];
    return NULL;
}

void list_push (list_t *list, void *elem) {
    (list->size)++;
    list->elems = realloc(list->elems, (list->size) * sizeof(void *));
    list->elems[list->size - 1] = elem;
}

int list_size (list_t *list) {
    return list->size;
}

void list_free (list_t *list) {
    int i;
    for (i = 0; i < list->size; i++)
        list->free_func(list->elems[i]);
    free(list->elems);
    free(list);
}
