#include "randomizer.h"
#include "mutex.h"
#include <time.h>
#include <stdlib.h>

static void *randomizer_random (void *argss) {
    shared_t *args = (shared_t *)argss;
    srand(time(NULL));
    while (1) {
        mutex_lock(args->mu);
        *(args->num) = rand() % 201 - 100;
        mutex_unlock(args->mu);
    }
    return NULL;
}

thread_t *randomizer_create(shared_t *data) {
    thread_t * thread = thread_create_args(randomizer_random, data);
    return thread;
}
