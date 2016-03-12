#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "text.h"

// unit-test function
static void new_void_zeroCount(void **state)
{
    text_t * text = text_new();
    assert_int_equal(text_getCount(text), 0);
    text_free(text);
}

static void insert_oneSentence_countOnePlaceZeroFormatTwo(void **state)
{
    text_t * text = text_new();

    int place = 0, format = 2;
    char sentence[L];
    strcpy (sentence, "Zhenya");

    text_insert (text, place, sentence, format);
    assert_int_equal (text_getCount(text), 1);
    assert_int_equal (text_getFormat(text, place), format);
    assert_string_equal (text_getString(text, place), sentence);
    text_free(text);
}

static void delete_hasOneInertedSentence_CountZero(void **state)
{
    text_t * text = text_new();

    int place = 0, format = 2;
    char sentence[L];
    strcpy (sentence, "Zhenya");

    text_insert (text, place, sentence, format);

    text_delete (text, place);

    assert_int_equal(text_getCount(text), 0);
    text_free(text);
}

int main(void) {
   const struct CMUnitTest tests[] =
    {
        cmocka_unit_test (new_void_zeroCount),
        cmocka_unit_test (insert_oneSentence_countOnePlaceZeroFormatTwo),
        cmocka_unit_test (delete_hasOneInertedSentence_CountZero)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
    return 0;
}
