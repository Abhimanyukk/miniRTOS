/* Logger unit tests */
#include "test_assert.h"
#include "mock_platform.h"
#include "logger/logger.h"
#include <string.h>

/* Test: log_init resets state */
static void test_log_init(void)
{
    mock_reset();
    log_init();

    TEST_ASSERT_EQUAL(0, mock_get_log_count());
}

/* Test: LOG_INFO produces output with correct level tag */
static void test_log_info_output(void)
{
    mock_reset();
    mock_set_time_ms(1000);
    log_init();

    LOG_INFO("hello %s", "world");

    TEST_ASSERT_EQUAL(1, mock_get_log_count());
    TEST_ASSERT_STR_CONTAINS(mock_get_log(0), "[INFO]");
    TEST_ASSERT_STR_CONTAINS(mock_get_log(0), "hello world");
    TEST_ASSERT_STR_CONTAINS(mock_get_log(0), "1000 ms");
}

/* Test: LOG_ERROR produces output with correct level tag */
static void test_log_error_output(void)
{
    mock_reset();
    mock_set_time_ms(500);
    log_init();

    LOG_ERROR("fail code %d", 42);

    TEST_ASSERT_EQUAL(1, mock_get_log_count());
    TEST_ASSERT_STR_CONTAINS(mock_get_log(0), "[ERROR]");
    TEST_ASSERT_STR_CONTAINS(mock_get_log(0), "fail code 42");
}

/* Test: LOG_WARN produces output with correct level tag */
static void test_log_warn_output(void)
{
    mock_reset();
    log_init();

    LOG_WARN("caution");

    TEST_ASSERT_EQUAL(1, mock_get_log_count());
    TEST_ASSERT_STR_CONTAINS(mock_get_log(0), "[WARN]");
    TEST_ASSERT_STR_CONTAINS(mock_get_log(0), "caution");
}

/* Test: multiple log calls produce multiple outputs */
static void test_log_multiple_writes(void)
{
    mock_reset();
    log_init();

    LOG_INFO("msg1");
    LOG_INFO("msg2");
    LOG_INFO("msg3");

    TEST_ASSERT_EQUAL(3, mock_get_log_count());
    TEST_ASSERT_STR_CONTAINS(mock_get_log(0), "msg1");
    TEST_ASSERT_STR_CONTAINS(mock_get_log(1), "msg2");
    TEST_ASSERT_STR_CONTAINS(mock_get_log(2), "msg3");
}

/* Test: timestamp changes between log calls */
static void test_log_timestamp_changes(void)
{
    mock_reset();
    log_init();

    mock_set_time_ms(100);
    LOG_INFO("first");
    mock_set_time_ms(200);
    LOG_INFO("second");

    TEST_ASSERT_STR_CONTAINS(mock_get_log(0), "100 ms");
    TEST_ASSERT_STR_CONTAINS(mock_get_log(1), "200 ms");
}

int main(void)
{
    printf("=== Logger Unit Tests ===\n");

    RUN_TEST(test_log_init);
    RUN_TEST(test_log_info_output);
    RUN_TEST(test_log_error_output);
    RUN_TEST(test_log_warn_output);
    RUN_TEST(test_log_multiple_writes);
    RUN_TEST(test_log_timestamp_changes);

    TEST_REPORT();
}
