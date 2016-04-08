#include <conio.h>
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
        if (number == 1) gamer_play (game, gamer1, command);
            else if (number == 2) gamer_play (game, gamer2, command);
        system ("CLS");
        game_show (game);
    }

    gamer_free (gamer1);
    gamer_free (gamer2);
    game_free (game);
    return 0;
}
