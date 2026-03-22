/* Minimal test framework - no external dependencies */
#ifndef TEST_ASSERT_H
#define TEST_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

#define TEST_ASSERT_EQUAL(expected, actual)                             \
    do                                                                  \
    {                                                                   \
        tests_run++;                                                    \
        if ((expected) == (actual))                                     \
        {                                                               \
            tests_passed++;                                             \
        }                                                               \
        else                                                            \
        {                                                               \
            tests_failed++;                                             \
            printf("  FAIL: %s:%d: expected %d, got %d\n",              \
                   __FILE__, __LINE__, (int)(expected), (int)(actual)); \
        }                                                               \
    } while (0)

#define TEST_ASSERT_TRUE(cond)                                              \
    do                                                                      \
    {                                                                       \
        tests_run++;                                                        \
        if ((cond))                                                         \
        {                                                                   \
            tests_passed++;                                                 \
        }                                                                   \
        else                                                                \
        {                                                                   \
            tests_failed++;                                                 \
            printf("  FAIL: %s:%d: condition false\n", __FILE__, __LINE__); \
        }                                                                   \
    } while (0)

#define TEST_ASSERT_STR_CONTAINS(haystack, needle)                \
    do                                                            \
    {                                                             \
        tests_run++;                                              \
        if (strstr((haystack), (needle)) != NULL)                 \
        {                                                         \
            tests_passed++;                                       \
        }                                                         \
        else                                                      \
        {                                                         \
            tests_failed++;                                       \
            printf("  FAIL: %s:%d: \"%s\" not found in \"%s\"\n", \
                   __FILE__, __LINE__, (needle), (haystack));     \
        }                                                         \
    } while (0)

#define RUN_TEST(test_func)                      \
    do                                           \
    {                                            \
        printf("  Running %s...\n", #test_func); \
        test_func();                             \
    } while (0)

#define TEST_REPORT()                                                 \
    do                                                                \
    {                                                                 \
        printf("\n--- Results: %d passed, %d failed, %d total ---\n", \
               tests_passed, tests_failed, tests_run);                \
        return (tests_failed > 0) ? 1 : 0;                            \
    } while (0)

#endif /* TEST_ASSERT_H */
