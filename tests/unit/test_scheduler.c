/* Scheduler unit tests */
#include "test_assert.h"
#include "mock_platform.h"
#include "scheduler/scheduler.h"
#include "config/minirtos_config.h"

static int counter_a = 0;
static int counter_b = 0;

static void task_a(void) { counter_a++; }
static void task_b(void) { counter_b++; }

/* Test: scheduler_init resets state */
static void test_scheduler_init(void)
{
    scheduler_init();
    mock_set_time_ms(0);
    counter_a = 0;

    /* After init, run_once should do nothing (no tasks) */
    scheduler_run_once();
    TEST_ASSERT_EQUAL(0, counter_a);
}

/* Test: single task runs when period elapses */
static void test_single_task_runs(void)
{
    counter_a = 0;
    scheduler_init();
    mock_set_time_ms(0);

    scheduler_add_task(task_a, 100);

    /* At time 0: now=0, last_run=0, delta=0, period=100 -> 0 >= 100 is false */
    scheduler_run_once();
    TEST_ASSERT_EQUAL(0, counter_a);

    /* Advance to 100ms */
    mock_set_time_ms(100);
    scheduler_run_once();
    TEST_ASSERT_EQUAL(1, counter_a);

    /* At 150ms, not enough time elapsed since last run (100) */
    mock_set_time_ms(150);
    scheduler_run_once();
    TEST_ASSERT_EQUAL(1, counter_a);

    /* At 200ms, should run again */
    mock_set_time_ms(200);
    scheduler_run_once();
    TEST_ASSERT_EQUAL(2, counter_a);
}

/* Test: multiple tasks with different periods */
static void test_multiple_tasks(void)
{
    counter_a = 0;
    counter_b = 0;
    scheduler_init();
    mock_set_time_ms(0);

    scheduler_add_task(task_a, 100); /* every 100ms */
    scheduler_add_task(task_b, 200); /* every 200ms */

    mock_set_time_ms(100);
    scheduler_run_once();
    TEST_ASSERT_EQUAL(1, counter_a);
    TEST_ASSERT_EQUAL(0, counter_b);

    mock_set_time_ms(200);
    scheduler_run_once();
    TEST_ASSERT_EQUAL(2, counter_a);
    TEST_ASSERT_EQUAL(1, counter_b);

    mock_set_time_ms(300);
    scheduler_run_once();
    TEST_ASSERT_EQUAL(3, counter_a);
    TEST_ASSERT_EQUAL(1, counter_b);

    mock_set_time_ms(400);
    scheduler_run_once();
    TEST_ASSERT_EQUAL(4, counter_a);
    TEST_ASSERT_EQUAL(2, counter_b);
}

/* Test: adding more than MAX_TASKS is silently ignored */
static void test_max_tasks_limit(void)
{
    scheduler_init();
    mock_set_time_ms(0);

    for (int i = 0; i < MAX_TASKS; i++)
    {
        scheduler_add_task(task_a, 100);
    }
    /* This one should be silently dropped */
    scheduler_add_task(task_b, 100);

    mock_set_time_ms(100);
    counter_a = 0;
    counter_b = 0;
    scheduler_run_once();

    TEST_ASSERT_EQUAL(MAX_TASKS, counter_a);
    TEST_ASSERT_EQUAL(0, counter_b); /* task_b was not added */
}

/* Test: reinit clears all tasks */
static void test_reinit_clears_tasks(void)
{
    counter_a = 0;
    scheduler_init();
    scheduler_add_task(task_a, 100);

    scheduler_init(); /* reinit */
    mock_set_time_ms(100);
    scheduler_run_once();

    TEST_ASSERT_EQUAL(0, counter_a); /* no tasks after reinit */
}

int main(void)
{
    printf("=== Scheduler Unit Tests ===\n");

    RUN_TEST(test_scheduler_init);
    RUN_TEST(test_single_task_runs);
    RUN_TEST(test_multiple_tasks);
    RUN_TEST(test_max_tasks_limit);
    RUN_TEST(test_reinit_clears_tasks);

    TEST_REPORT();
}
