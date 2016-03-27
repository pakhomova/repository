#include "randomizer.h"
#include "mutex.h"
#include <time.h>
#include <stdlib.h>

void *randomizer_random (void *argss) {
    shared_t *args = (shared_t *)argss;
    srand(time(NULL));
    while (1) {
        mutex_lock(args->mu);
        *(args->num) = rand() % 201 - 100;
        mutex_unlock(args->mu);
    }
    return NULL;
}
