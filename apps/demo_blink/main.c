#include "scheduler/scheduler.h"
#include "logger/logger.h"

static void blink_task(void)
{
    LOG_INFO("blink toggle");
}

int main(void)
{
    log_init();
    scheduler_init();

    scheduler_add_task(blink_task, 1000);

    LOG_INFO("demo_blink started");
    scheduler_run();

    return 0;
}
