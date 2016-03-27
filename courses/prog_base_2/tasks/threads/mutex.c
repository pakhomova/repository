#include <windows.h>
#include "mutex.h"

struct mutex_s {
    HANDLE win_mutex;
};

mutex_t * mutex_new(void) {
    mutex_t * ins = malloc(sizeof(struct mutex_s));
    ins->win_mutex = CreateMutex(
        NULL,
        FALSE,
        NULL);
    return ins;
}
void mutex_free(mutex_t * self) {
    CloseHandle(self->win_mutex);
    free(self);
}

void mutex_lock(mutex_t * self) {
    WaitForSingleObject(self->win_mutex, INFINITE);
}

void mutex_unlock(mutex_t * self) {
    ReleaseMutex(self->win_mutex);
}

