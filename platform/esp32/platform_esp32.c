/* ESP32 platform implementation - stub
 * Requires ESP-IDF to build.
 * Uncomment and adapt when targeting ESP32.
 */

#if 0

#include "../platform.h"
#include "esp_timer.h"

uint32_t platform_get_time_ms(void) {
    return (uint32_t)(esp_timer_get_time() / 1000);
}

void platform_log_output(const char *msg) {
    printf("%s\n", msg);
}

void platform_enter_critical(void) {
    /* TODO: use portENTER_CRITICAL */
}

void platform_exit_critical(void) {
    /* TODO: use portEXIT_CRITICAL */
}

#endif
