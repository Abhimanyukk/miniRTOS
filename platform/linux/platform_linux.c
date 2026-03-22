#include "../platform.h"
#include <stdio.h>
#include <time.h>

uint32_t platform_get_time_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void platform_log_output(const char *msg)
{
    printf("%s\n", msg);
}

void platform_enter_critical(void)
{
    /* No-op on Linux (single-threaded context) */
}

void platform_exit_critical(void)
{
    /* No-op on Linux (single-threaded context) */
}
