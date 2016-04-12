#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "game.h"
#include "gamer.h"
#include "gamer_tests.h"
#include "game_tests.h"

int main() {
    gamer_runTests();
    game_runTests();
    game_t *game = game_newGame();
    gamer_t *gamer1 = gamer_newGamer(1);
    gamer_t *gamer2 = gamer_newGamer(2);

    char c;
    ErrorCode err;

    while (c = getch()) {
        int command = 0, number = 0;
        if (c == '0') break;
        switch (c) {
            case 's':
                command = 0;
                number = 1;
                break;
            case 'w':
                command = 1;
                number = 1;
                break;
            case 'a':
                command = 2;
                number = 1;
                break;
            case 'd':
                command = 3;
                number = 1;
                break;
            case 80:
                command = 0;
                number = 2;
                break;
            case 72:
                command = 1;
                number = 2;
                break;
            case 75:
                command = 2;
                number = 2;
                break;
            case 77:
                command = 3;
                number = 2;
                break;
        }
        if (number == 1) err = gamer_play (gamer1, game, command);
            else if (number == 2) err = gamer_play (gamer2, game, command);
        if (err != RESULT_OK) printf (gamer_errstr(err));
        system ("CLS");
        err = game_show (game);
        if (err != RESULT_OK) printf (game_errstr(err));
    }

    err = gamer_free (gamer1);
    if (err != RESULT_OK) printf (gamer_errstr(err));
    err = gamer_free (gamer2);
    if (err != RESULT_OK) printf (gamer_errstr(err));
    err = game_free (game);
    if (err != RESULT_OK) printf (game_errstr(err));
    return 0;
}
