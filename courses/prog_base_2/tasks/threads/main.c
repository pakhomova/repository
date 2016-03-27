#include <stdio.h>
#include <stdlib.h>
#include "randomizer.h"
#include "thread.h"
#include "positiveWriter.h"
#include "mutex.h"

int main()
{
    shared_t sharedData;
    int x = 0;
    sharedData.num = &x;
    sharedData.mu = mutex_new();

    randomizer_t *randomizer1 = randomizer_costructor(&sharedData);
    randomizer_t *randomizer2 = randomizer_costructor(&sharedData);
    randomizer_t *randomizer3 = randomizer_costructor(&sharedData);

    positiveWriter_t *positiveWriter = positiveWriter_costructor(&sharedData);

    positiveWriter_join (positiveWriter);

    randomizer_destructor (randomizer1);
    randomizer_destructor (randomizer2);
    randomizer_destructor (randomizer3);

    positiveWriter_destructor (positiveWriter);

    mutex_free(sharedData.mu);
    return 0;
}
