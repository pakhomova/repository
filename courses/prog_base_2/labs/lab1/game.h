#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define N 1000

typedef struct game_s game_t;

typedef enum {
    RESULT_OK,
    WRONG_COMMAND,
    WRONG_GAMER,
    OVERFLOW,
    WRONG_GAME
} ErrorCode;

game_t *game_newGame (void);
ErrorCode game_free (game_t *self);

const char *game_errstr (ErrorCode errcode);

ErrorCode game_add (game_t *self, int command, int number);
ErrorCode game_show (game_t *self);
int game_getLastCommand (game_t *self);
int game_getQueueEnd (game_t *self);
int game_getGamerOfLastCommand (game_t *self);

#endif
