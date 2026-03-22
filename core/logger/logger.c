#include "logger.h"
#include "../config/minirtos_config.h"
#include "../../platform/platform.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static const char *level_strings[] = {"INFO", "WARN", "ERROR"};

typedef struct
{
    char messages[LOG_BUFFER_SIZE][LOG_MSG_MAX_LEN];
    uint8_t head;
    uint8_t count;
} log_ring_buffer_t;

static log_ring_buffer_t log_buffer;

void log_init(void)
{
    log_buffer.head = 0;
    log_buffer.count = 0;
    memset(log_buffer.messages, 0, sizeof(log_buffer.messages));
}

void log_write(uint8_t level, const char *fmt, ...)
{
    char buf[LOG_MSG_MAX_LEN];
    uint32_t time_ms = platform_get_time_ms();

    const char *lvl_str = (level <= LOG_LEVEL_ERROR) ? level_strings[level] : "???";

    int offset = snprintf(buf, sizeof(buf), "[%u ms] [%s] ", (unsigned)time_ms, lvl_str);

    va_list args;
    va_start(args, fmt);
    vsnprintf(buf + offset, sizeof(buf) - (size_t)offset, fmt, args);
    va_end(args);

    /* Store in ring buffer */
    platform_enter_critical();
    uint8_t idx = (log_buffer.head + log_buffer.count) % LOG_BUFFER_SIZE;
    if (log_buffer.count < LOG_BUFFER_SIZE)
    {
        log_buffer.count++;
    }
    else
    {
        log_buffer.head = (log_buffer.head + 1) % LOG_BUFFER_SIZE;
    }
    strncpy(log_buffer.messages[idx], buf, LOG_MSG_MAX_LEN - 1);
    log_buffer.messages[idx][LOG_MSG_MAX_LEN - 1] = '\0';
    platform_exit_critical();

    /* Also output immediately */
    platform_log_output(buf);
}
