#ifndef GAMER_H_INCLUDED
#define GAMER_H_INCLUDED

#include "game.h"

typedef struct gamer_s gamer_t;

gamer_t *gamer_newGamer (int number);
void gamer_free (gamer_t *self);

void gamer_play (game_t *game, gamer_t *self, int command);
int gamer_getNumber (gamer_t *self);

#endif
