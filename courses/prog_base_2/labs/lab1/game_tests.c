#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "game.h"

static void newGame_void_zeroQueueEnd(void **state) {
    game_t * game = game_newGame();
    assert_int_equal(game_getQueueEnd(game), 0);
    game_free(game);
}

static void add_emptyQueueCommandOneFirstNumberOfPlayer_firstPlayerAddedCommandOneInQueueOneQueueEnd(void **state) {
    game_t * game = game_newGame();
    game_add (game, 1, 1);
    assert_int_equal(game_getLastCommand(game), 1);
    assert_int_equal(game_getGamerOfLastCommand(game), 1);
    assert_int_equal(game_getQueueEnd(game), 1);
    game_free(game);
}

void game_runTests(void){

	const struct CMUnitTest tests[] =
	{
		cmocka_unit_test(newGame_void_zeroQueueEnd),
		cmocka_unit_test(add_emptyQueueCommandOneFirstNumberOfPlayer_firstPlayerAddedCommandOneInQueueOneQueueEnd)
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
