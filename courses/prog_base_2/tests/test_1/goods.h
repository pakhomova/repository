#ifndef GOODS_H
#define GOODS_H

#define LEN 30

typedef struct goods_s {
    char name[LEN];
    int volume;
} goods_t;

goods_t *goods_new (char *name, int volume);
goods_t *goods_copy (goods_t *goods);
void goods_free (goods_t *self);

#endif
