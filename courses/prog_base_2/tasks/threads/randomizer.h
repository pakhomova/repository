#ifndef RANDOMIZER_H_INCLUDED
#define RANDOMIZER_H_INCLUDED

#include "mutex.h"
#include "thread.h"

typedef struct shared_s {
    int *num;
    mutex_t *mu;
} shared_t;

thread_t *randomizer_create(shared_t *data);

#endif
