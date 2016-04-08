#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define N 1000

typedef struct game_s game_t;

game_t *game_newGame (void);
void game_free (game_t *self);

void game_add (game_t *self, int command, int number);
void game_show (game_t *self);
int game_getLastCommand (game_t *self);
int game_getQueueEnd (game_t *self);
int game_getGamerOfLastCommand (game_t *self);

#endif
