#ifndef GAMER_H_INCLUDED
#define GAMER_H_INCLUDED

#include "game.h"

typedef struct gamer_s gamer_t;

gamer_t *gamer_newGamer (int number);
ErrorCode gamer_free (gamer_t *self);
const char *gamer_errstr (ErrorCode errcode);

ErrorCode gamer_play (gamer_t *self, game_t *game, int command);
int gamer_getNumber (gamer_t *self);

#endif
