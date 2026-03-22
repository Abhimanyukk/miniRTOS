#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

uint32_t platform_get_time_ms(void);
void platform_log_output(const char *msg);
void platform_enter_critical(void);
void platform_exit_critical(void);

#endif /* PLATFORM_H */
