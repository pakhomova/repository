#include "list.h"
#include "string.h"

#define SIZE 20

typedef struct supply_s {
    char time[SIZE];
    goods[];
} supply_t;

struct list {
    int count;
    supply_t sup[SIZE];
};

list_pushBack (list_t *self, supply_t ) {
}
