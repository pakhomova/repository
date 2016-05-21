#ifndef STORE_H
#define STORE_H

#include "goods.h"

#define SIZEGOOD 30

typedef struct store_s {
    int size;
    int count;
    goods_t goods[SIZEGOOD];
} store_t;

store_t *store_new ();
void store_free (store_t *self);
void push_back (store_t *self, goods_t *goods);
int storeVolume (store_t *self);
double storePercent (store_t *self);

#endif

