/* Mock platform for unit testing
 * Provides controllable time and captures log output.
 */
#include "platform.h"
#include <string.h>
#include <stdio.h>

static uint32_t mock_time_ms = 0;
#define MOCK_LOG_MAX 64
#define MOCK_LOG_LEN 128
static char mock_log_output[MOCK_LOG_MAX][MOCK_LOG_LEN];
static int mock_log_count = 0;

/* Time control */
void mock_set_time_ms(uint32_t t) { mock_time_ms = t; }
void mock_advance_time_ms(uint32_t delta) { mock_time_ms += delta; }

/* Log inspection */
int mock_get_log_count(void) { return mock_log_count; }
const char *mock_get_log(int index)
{
    if (index < 0 || index >= mock_log_count)
        return "";
    return mock_log_output[index];
}

void mock_reset(void)
{
    mock_time_ms = 0;
    mock_log_count = 0;
    memset(mock_log_output, 0, sizeof(mock_log_output));
}

/* Platform interface implementation */
uint32_t platform_get_time_ms(void)
{
    return mock_time_ms;
}

void platform_log_output(const char *msg)
{
    if (mock_log_count < MOCK_LOG_MAX)
    {
        strncpy(mock_log_output[mock_log_count], msg, MOCK_LOG_LEN - 1);
        mock_log_output[mock_log_count][MOCK_LOG_LEN - 1] = '\0';
        mock_log_count++;
    }
}

void platform_enter_critical(void) { /* no-op in test */ }
void platform_exit_critical(void) { /* no-op in test */ }
