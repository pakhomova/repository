#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

typedef struct thread_s thread_t;
typedef void * (*thread_func_t)(void *);

thread_t * thread_create_args(thread_func_t func, void * args);
void thread_free(thread_t * self);

int thread_join(const thread_t * self);

#endif


