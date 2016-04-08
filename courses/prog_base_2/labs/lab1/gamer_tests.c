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
    gamer_play (game, gamer, 1);
    assert_int_equal(game_getLastCommand (game), 1);
    gamer_free(gamer);
    game_free(game);
}

void gamer_runTests(void){

	const struct CMUnitTest tests[] =
	{
		cmocka_unit_test(newGamer_firstGamer_newGamerHasFirstNumber),
		cmocka_unit_test(play_CommandOne_CommandOneIsAddedInGameAsALastCommand)
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
