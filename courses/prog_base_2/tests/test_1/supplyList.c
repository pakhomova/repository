#include "supplyList.h"
#include "stdlib.h"

supplyList_t *supplyList_new () {
    supplyList_t *spl = (supplyList_t *)malloc(sizeof(struct supplyList_s));
    spl->count = 0;
    return spl;
}

void supplyList_free (supplyList_t *self) {
    free (self);
}

void push_back (supplyList_t *self, supply_t *supply) {
    self->count++;
    self->supp[self->count - 1] = *supply_copy(supply);
}

supply_t *getn (supplyList_t *self, int n) {
    supply_t *supp = malloc(n * sizeof(struct supply_s));
    int i = self->count - 1, k = 0;
    while (i >= 0 && k < n) {
        supp[k] = self->supp[i];
        k++;
        i--;
    }
    return supp;
}



