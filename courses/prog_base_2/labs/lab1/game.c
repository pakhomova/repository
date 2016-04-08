#include "game.h"
#include <stdlib.h>
#include <stdio.h>

const char *commands[] = {"Down!", "Up!", "Left!", "Right!"};

static struct element {
    int command;
    int numberOfGamer;
};

static struct game_s {
    int queueEnd; //куда будем добавлять следующий элемент
    struct element queueArray [N];
};

game_t *game_newGame (void) {
    game_t *game_new = malloc(sizeof(struct game_s));
    game_new->queueEnd = 0;
    return game_new;
}

void game_free (game_t *self) {
    free (self);
}

void game_add (game_t *self, int command, int number) {
    self->queueArray[self->queueEnd].command = command;
    self->queueArray[self->queueEnd].numberOfGamer = number;
    self->queueEnd++;
}

void game_show (game_t *self) {
    int i;
    for (i = 0; i < self->queueEnd; i++)
        printf ("%s, %i player\n", commands[self->queueArray[i].command], self->queueArray[i].numberOfGamer);
}

int game_getLastCommand (game_t *self){                //для тестов
    return self->queueArray[self->queueEnd - 1].command;
}

int game_getGamerOfLastCommand (game_t *self){                //для тестов
    return self->queueArray[self->queueEnd - 1].numberOfGamer;
}

int game_getQueueEnd (game_t *self){                   //для тестов
    return self->queueEnd;
}
