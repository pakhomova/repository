#ifndef RANDOMIZER_H_INCLUDED
#define RANDOMIZER_H_INCLUDED

#include "mutex.h"
#include "thread.h"

typedef struct randomizer_s randomizer_t;

typedef struct shared_s {
    int *num;
    mutex_t *mu;
} shared_t;

randomizer_t *randomizer_costructor (shared_t *data);
void randomizer_destructor (randomizer_t *randomizer);

#endif
