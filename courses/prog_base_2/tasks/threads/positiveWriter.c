#include "mutex.h"
#include "positiveWriter.h"
#include <stdio.h>
#include <windows.h>

static void *positiveWriter_write(void *argss) {
    shared_t *args = (shared_t *)argss;
    while (1) {
        mutex_lock(args->mu);
        if(*(args->num) > 0) {
            printf("%i\n", *(args->num));
        }
        mutex_unlock(args->mu);
        Sleep(3);
    }
    return NULL;
}

thread_t *positiveWriter_create(shared_t *data) {
    thread_t * thread = thread_create_args(positiveWriter_write, data);
    return thread;
}
