#include "supply.h"
#include "string.h"
#include "stdlib.h"

supply_t *supply_new (goods_t *goods, char *time) {
    supply_t *supply = (supply_t *)malloc(sizeof(struct supply_s));
    supply->goods = goods_copy(goods);
    strcpy (supply->time, time);
    return supply;
}

supply_t *supply_copy (supply_t *supply) {
    supply_t *supp = (supply_t *)malloc(sizeof(struct supply_s));
    supp->goods = goods_copy(supply->goods);
    strcpy (supp->time, supply->time);
    return supp;
}

void supply_free (supply_t *self) {
    goods_free (self->goods);
    free (self);
}

