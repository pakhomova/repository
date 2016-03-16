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

static void writeFormat_insertOneSentenceWithThirdFormat_CountOnePlaceZeroFormatThird (void **state) {
    text_t *text = text_new();
    int place = 0, format = 3;
    char sentence[L];
    strcpy (sentence, "Zhenya");

    text_insert (text, place, sentence, format);

    text_t *text1 = text_new();
    text1 = text_writeFormat(text,format);

    assert_int_equal (text_getCount(text1), 1);
    assert_string_equal (text_getString(text1, place), sentence);
    assert_int_equal (text_getFormat(text1, place), format);
}

static void writeFormat_insertOneSentenceWithFirstFormat_CountZero (void **state) {
    text_t *text = text_new();
    int place = 0, format = 1;
    char sentence[L];
    strcpy (sentence, "Zhenya");

    text_insert (text, place, sentence, format);

    text_t *text1 = text_new();
    text1 = text_writeFormat(text,0);

    assert_int_equal (text_getCount(text1), 0);
}

static void writeFormat_insertTwoSentenceWithFirstAndSecondFormat_CountOnePlaceZeroFormatSecond (void **state) {
    text_t *text = text_new();

    char sentence1[L], sentence2[L];
    strcpy (sentence1, "Zhenya1");
    strcpy (sentence2, "Zhenya2");

    text_insert (text, 0, sentence1, 1);
    text_insert (text, 1, sentence2, 2);

    text_t *text1 = text_new();
    text1 = text_writeFormat(text, 2);

    assert_int_equal (text_getCount(text1), 1);
    assert_string_equal (text_getString(text1, 0), sentence2);
    assert_int_equal (text_getFormat(text1, 0), 2);
}

int main(void) {
   const struct CMUnitTest tests[] =
    {
        cmocka_unit_test (new_void_zeroCount),
        cmocka_unit_test (insert_oneSentence_countOnePlaceZeroFormatTwo),
        cmocka_unit_test (delete_hasOneInertedSentence_CountZero),
        cmocka_unit_test (writeFormat_insertOneSentenceWithThirdFormat_CountOnePlaceZeroFormatThird),
        cmocka_unit_test (writeFormat_insertOneSentenceWithFirstFormat_CountZero),
        cmocka_unit_test (writeFormat_insertTwoSentenceWithFirstAndSecondFormat_CountOnePlaceZeroFormatSecond)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
    return 0;
}
