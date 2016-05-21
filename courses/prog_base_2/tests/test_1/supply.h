#ifndef SUPPLY_H
#define SUPPLY_H

#include "goods.h"

#define TIMELEN 10

typedef struct supply_s {
    char time[TIMELEN];
    goods_t *goods;
} supply_t;

supply_t *supply_new (goods_t *goods, char *time);
supply_t *supply_copy (supply_t *supply);
void supply_free (supply_t *self);

#endif
