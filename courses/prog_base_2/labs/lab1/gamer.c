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

ErrorCode gamer_free (gamer_t *self) {
    if (self == NULL) return WRONG_GAMER;
    free (self);
    return RESULT_OK;
}

int gamer_getNumber (gamer_t *self) {   //для тестов
    return self->number;
}

ErrorCode gamer_play (gamer_t *self, game_t *game, int command) {
    if (game == NULL) return WRONG_GAME;
    if (self == NULL) return WRONG_GAMER;
    if (command < 0 || command > 4) return WRONG_COMMAND;

    game_add (game, command, self->number);
    return RESULT_OK;
}


const char *gamer_errstr (ErrorCode errcode) {
    static const char *repr[] = {
        "RESULT_OK",
        "WRONG_COMMAND",
        "WRONG_GAMER",
        "OVERFLOW",
        "WRONG_GAME"
    };
    return repr[errcode];
}

