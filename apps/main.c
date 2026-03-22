#include "scheduler/scheduler.h"
#include "logger/logger.h"

int main(void)
{
    log_init();
    scheduler_init();

    LOG_INFO("miniRTOS started");

    return 0;
}
