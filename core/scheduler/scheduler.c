#include "scheduler.h"
#include "../config/minirtos_config.h"
#include "../../platform/platform.h"

typedef struct
{
    task_fn fn;
    uint32_t period_ms;
    uint32_t last_run_ms;
} task_t;

static task_t task_list[MAX_TASKS];
static uint8_t task_count = 0;

void scheduler_init(void)
{
    task_count = 0;
    for (uint8_t i = 0; i < MAX_TASKS; i++)
    {
        task_list[i].fn = (task_fn)0;
        task_list[i].period_ms = 0;
        task_list[i].last_run_ms = 0;
    }
}

void scheduler_add_task(task_fn fn, uint32_t period_ms)
{
    if (task_count >= MAX_TASKS)
    {
        return;
    }
    task_list[task_count].fn = fn;
    task_list[task_count].period_ms = period_ms;
    task_list[task_count].last_run_ms = 0;
    task_count++;
}

void scheduler_run_once(void)
{
    uint32_t now = platform_get_time_ms();
    for (uint8_t i = 0; i < task_count; i++)
    {
        if ((now - task_list[i].last_run_ms) >= task_list[i].period_ms)
        {
            task_list[i].last_run_ms = now;
            if (task_list[i].fn)
            {
                task_list[i].fn();
            }
        }
    }
}

void scheduler_run(void)
{
    while (1)
    {
        scheduler_run_once();
    }
}
