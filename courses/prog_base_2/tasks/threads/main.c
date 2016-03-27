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
    thread_t * radomizer1 = thread_create_args(randomizer_random, &sharedData);
    thread_t * radomizer2 = thread_create_args(randomizer_random, &sharedData);
    thread_t * radomizer3 = thread_create_args(randomizer_random, &sharedData);
    thread_t * positiveWriter = thread_create_args(positiveWriter_write, &sharedData);

    thread_join(positiveWriter);
    thread_free(radomizer1);
    thread_free(radomizer2);
    thread_free(radomizer3);
    thread_free(positiveWriter);

    mutex_free(sharedData.mu);
    return 0;
}
