#include "goods.h"
#include "string.h"
#include "stdlib.h"

goods_t *goods_new (char *name, int volume) {
    goods_t *goods = (goods_t *)malloc(sizeof(struct goods_s));
    strcpy (goods->name, name);
    goods->volume = volume;
    return goods;
}

goods_t *goods_copy (goods_t *goods) {
    return goods_new(goods->name, goods->volume);
}

void goods_free (goods_t *self) {
    free (self);
}
