#ifndef MOCK_PLATFORM_H
#define MOCK_PLATFORM_H

#include <stdint.h>

void mock_set_time_ms(uint32_t t);
void mock_advance_time_ms(uint32_t delta);
int mock_get_log_count(void);
const char *mock_get_log(int index);
void mock_reset(void);

#endif /* MOCK_PLATFORM_H */
