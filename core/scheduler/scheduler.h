#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

typedef void (*task_fn)(void);

void scheduler_init(void);
void scheduler_add_task(task_fn fn, uint32_t period_ms);
void scheduler_run(void);
void scheduler_run_once(void);

#endif /* SCHEDULER_H */
