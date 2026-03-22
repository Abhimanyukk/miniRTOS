#include "../../core/scheduler/scheduler.h"
#include "../../core/logger/logger.h"

static void task_a(void)
{
    LOG_INFO("task A running");
    for (int i = 0; i < 1000000; i++)
    {
        for (int i = 0; i < 1000; i++)
        {
            /* Simulate work */
        }
        /* Simulate work */
    }
}

static void task_b(void)
{
    LOG_INFO("task B running");
}

int main(void)
{
    log_init();
    scheduler_init();

    scheduler_add_task(task_a, 500);
    scheduler_add_task(task_b, 1000);

    LOG_INFO("demo_tasks started");
    scheduler_run();

    return 0;
}
