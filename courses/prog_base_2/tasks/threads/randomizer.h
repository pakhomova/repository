#ifndef RANDOMIZER_H_INCLUDED
#define RANDOMIZER_H_INCLUDED

#include "mutex.h"

typedef struct shared_s {
    int *num;
    mutex_t *mu;
} shared_t;

void *randomizer_random (void *args);

#endif
