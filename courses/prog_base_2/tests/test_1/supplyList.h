#ifndef SUPPLYLIST_H
#define SUPPLYLIST_H

#include "supply.h"

#define SIZE 30

typedef struct supplyList_s {
    int count;
    supply_t supp[SIZE];
} supplyList_t;

supplyList_t *supplyList_new ();
void supplyList_free (supplyList_t *self);
void push_back (supplyList_t *self, supply_t *supply);
supply_t *getn (supplyList_t *self, int n);

#endif
