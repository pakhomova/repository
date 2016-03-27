#include "mutex.h"
#include "positiveWriter.h"
#include <stdio.h>
#include <windows.h>

struct positiveWriter_s {
    thread_t *thread;
};

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

positiveWriter_t *positiveWriter_costructor (shared_t *data) {
    positiveWriter_t *positiveWriter = malloc(sizeof(positiveWriter_t));
    positiveWriter->thread = thread_create_args(positiveWriter_write, data);
    return positiveWriter;
}

void positiveWriter_join (positiveWriter_t *positiveWriter) {
    thread_join(positiveWriter->thread);
}

void positiveWriter_destructor (positiveWriter_t *positiveWriter) {
    thread_free(positiveWriter->thread);
    free (positiveWriter);
}
