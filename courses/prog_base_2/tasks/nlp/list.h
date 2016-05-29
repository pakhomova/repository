#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct list_s list_t;

typedef void (*list_free_func_t)(void *elem);

list_t *list_new (list_free_func_t free_func);
void *list_get (list_t *list, int index);
void list_push (list_t *list, void *elem);

/*int list_put(list_t *list, void *elem, int index) {
    if (index == list->size) {
        list_push(list, elem);
        return 1;
    } else if (index < list->size) {
        list->elems[index] = elem;
        return 1;
    }
    return 0;
}*/

/*int list_pop (list_t *list, int index) {
    if (index < list->size) {
        list->free_func(list->elems[index]);
        memmove(list->elems + index, list->elems + index + 1, (list->size - index - 1) * sizeof(void *));
        --list->size;
        list->elems = realloc(list->elems, list->size * sizeof(void *));
        return 1;
    }
    return 0;
}*/

int list_size (list_t *list);
void list_free (list_t *list);

#endif // LIST_H
