/* STM32 platform implementation - stub
 * Requires STM32 HAL or bare-metal setup to build.
 * Adapt when targeting STM32.
 */

#include "../platform.h"
#include "stm32f4xx_hal.h"

uint32_t platform_get_time_ms(void) {
    return HAL_GetTick();
}

void platform_log_output(const char *msg) {
    /* TODO: implement UART output */
    (void)msg;
}

void platform_enter_critical(void) {
    __disable_irq();
}

void platform_exit_critical(void) {
    __enable_irq();
}
