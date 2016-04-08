#include "gamer.h"
#include <stdlib.h>
#include <stdio.h>

static struct gamer_s {
    int number;
};

gamer_t *gamer_newGamer (int number) {
    gamer_t *gamer_new = malloc(sizeof(struct gamer_s));
    gamer_new->number = number;
    return gamer_new;
}

void gamer_free (gamer_t *self) {
    free (self);
}

int gamer_getNumber (gamer_t *self) {   //для тестов
    return self->number;
}

void gamer_play (game_t *game, gamer_t *self, int command) {
    game_add (game, command, self->number);
}
