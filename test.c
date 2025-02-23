/* See LICENSE file for copyright and license details. */

#include <stdint.h>
#include <stdlib.h>
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <ctype.h>

#include "compiler.h"
#include "cutest.h"

// type testing
static void
test_int_literal_has_digit_data(CuTest* tc)
{
        Token token = new_token((TokenType*)INT_LITERAL, (void*)"420");
        const char* str = (const char*)token.data;

        int all_digits = 1;
        for (int i = 0; str[i] != '\0'; i++) {
                if (!isdigit((unsigned char)str[i])) {
                        all_digits = 0;
                        break;
                }
        }

        CuAssertTrue(tc, all_digits);
}

// malloc testing
static void
test_malloc_token_arr(CuTest* tc)
{
        Token* tokens = (Token*)malloc(sizeof(Token) * 4);
        CuAssertTrue(tc, tokens != NULL);
        free(tokens);
}

static void
test_create_new_token(CuTest* tc)
{
        Token* tokens = (Token*)malloc(sizeof(Token) * 4);
        if (tokens == NULL) {
                perror("Failed to allocate token memory");
                free(tokens);
                return;
        }

        tokens[0] = new_token((TokenType*)INT_LITERAL, (char*)"foo");

        CuAssertStrEquals(tc, "foo", (char*)((tokens[0]).data));

        free(tokens);
}

static void
test_file_exists(CuTest* tc)
{
        char* path = "./test.zn";
        int exists = file_exists(path);
        CuAssertIntEquals(tc, exists, 1);
}

static void
test_file_not_exists(CuTest* tc)
{
        char* path = "./test_not_exists.zn";
        int exists = file_exists(path);
        CuAssertIntEquals(tc, exists, 0);
}

static CuSuite*
get_malloc_suite(void)
{
        CuSuite* suite = CuSuiteNew();
        SUITE_ADD_TEST(suite, test_malloc_token_arr);
        return suite;
}

static CuSuite*
get_typecheck_suite(void)
{
        CuSuite* suite = CuSuiteNew();
        SUITE_ADD_TEST(suite, test_int_literal_has_digit_data);
        return suite;
}

static CuSuite*
get_std_suite(void)
{
        CuSuite* suite = CuSuiteNew();
        SUITE_ADD_TEST(suite, test_create_new_token);
        SUITE_ADD_TEST(suite, test_file_exists);
        SUITE_ADD_TEST(suite, test_file_not_exists);
        return suite;
}

int
main(void)
{
        CuSuite* suite = CuSuiteNew();
        CuString* out = CuStringNew();

        CuSuiteAddSuite(suite, get_std_suite());
        CuSuiteAddSuite(suite, get_typecheck_suite());
        CuSuiteAddSuite(suite, get_malloc_suite());

        CuSuiteRun(suite);
        CuSuiteSummary(suite, out);
        CuSuiteDetails(suite, out);
        printf("%s\n", out->buffer);
        CuSuiteDelete(suite);
        return 1;
}
