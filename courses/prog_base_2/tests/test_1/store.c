#include "store.h"
#include "stdlib.h"

store_t *store_new (int volume) {
    store_t *st = (store_t *)malloc(sizeof(struct store_s));
    st->count = 0;
    st->size = volume;
    return st;
}

void store_free (store_t *self) {
    free (self);
}

void push_back (store_t *self, goods_t *goods) {
    self->count++;
    self->goods[self->count - 1] = *goods_copy(goods);
}

int storeVolume (store_t *self) {
    return self->size;
}

double storePercent (store_t *self) {
    int i;
    double sum = 0;
    for (i = 0; i < self->count; i++)
        sum += self->goods[i].volume;
    sum /= self->size;
    return sum;
}
