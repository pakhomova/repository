#ifndef POSITIVEWRITER_H_INCLUDED
#define POSITIVEWRITER_H_INCLUDED

#include "randomizer.h"
#include "thread.h"

typedef struct positiveWriter_s positiveWriter_t;

positiveWriter_t *positiveWriter_costructor (shared_t *data);
void positiveWriter_destructor (positiveWriter_t *positiveWriter);
void positiveWriter_join (positiveWriter_t *positiveWriter);

#endif

