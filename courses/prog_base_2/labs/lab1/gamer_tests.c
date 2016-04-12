#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "gamer.h"
#include "game.h"

static void newGamer_firstGamer_newGamerHasFirstNumber(void **state) {
    gamer_t * gamer = gamer_newGamer(1);
    assert_int_equal(gamer_getNumber(gamer), 1);
    gamer_free(gamer);
}

static void play_CommandOne_CommandOneIsAddedInGameAsALastCommand(void **state) {
    gamer_t * gamer = gamer_newGamer(1);
    game_t * game = game_newGame();
    gamer_play (gamer, game, 1);
    assert_int_equal(game_getLastCommand (game), 1);
    gamer_free(gamer);
    game_free(game);
}

/*static void play_NonexistentGameName_ErrorCodeFour(void **state) {
    gamer_t * gamer = gamer_newGamer(1);
    game_t * game = game_newGame();
    assert_int_equal(gamer_play (gamer, game1, 1), 4);
    gamer_free(gamer);
    game_free(game);
}

static void play_NonexistentGamerName_ErrorCodeTwo(void **state) {
    gamer_t * gamer = gamer_newGamer(1);
    game_t * game = game_newGame();
    assert_int_equal(gamer_play (gamer1, game, 1), 2);
    gamer_free(gamer);
    game_free(game);
}
*/
static void play_NonexistentCommand_ErrorCodeOne(void **state) {
    gamer_t * gamer = gamer_newGamer(1);
    game_t * game = game_newGame();
    assert_int_equal(gamer_play (gamer, game, -5), 1);
    gamer_free(gamer);
    game_free(game);
}

int gamer_runTests(void) {

	const struct CMUnitTest tests[] =
	{
		cmocka_unit_test(newGamer_firstGamer_newGamerHasFirstNumber),
		cmocka_unit_test(play_CommandOne_CommandOneIsAddedInGameAsALastCommand),
		//cmocka_unit_test(play_NonexistentGameName_ErrorCodeFour),
		//cmocka_unit_test(play_NonexistentGamerName_ErrorCodeTwo),
		cmocka_unit_test(play_NonexistentCommand_ErrorCodeOne)
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
