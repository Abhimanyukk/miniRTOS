#ifndef LOGGER_H
#define LOGGER_H

#include <stdint.h>

#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_WARN 1
#define LOG_LEVEL_ERROR 2

#define LOG_INFO(...) log_write(LOG_LEVEL_INFO, __VA_ARGS__)
#define LOG_WARN(...) log_write(LOG_LEVEL_WARN, __VA_ARGS__)
#define LOG_ERROR(...) log_write(LOG_LEVEL_ERROR, __VA_ARGS__)

void log_init(void);
void log_write(uint8_t level, const char *fmt, ...);

#endif /* LOGGER_H */
