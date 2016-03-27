#include "randomizer.h"
#include "mutex.h"
#include "thread.h"
#include <time.h>
#include <stdlib.h>

struct randomizer_s {
    thread_t *thread;
};

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

randomizer_t *randomizer_costructor (shared_t *data) {
    randomizer_t *randomizer = malloc(sizeof(randomizer_t));
    randomizer->thread = thread_create_args(randomizer_random, data);
    return randomizer;
}

void randomizer_destructor (randomizer_t *randomizer) {
    thread_free(randomizer->thread);
    free (randomizer);
}
