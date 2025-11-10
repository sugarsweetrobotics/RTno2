#ifndef DURATION_CLOCK_HEADER_FILE_INCLUDED
#define DURATION_CLOCK_HEADER_FILE_INCLUDED

#include <stdint.h>

using duration_t = uint32_t;
using duration_time_t = uint32_t;
static const duration_t INFINITE = 0xFFFFFFFF;

void DurationClock_tick();
duration_t DurationClock_tack();

duration_time_t DurationClock_now_ms();
#endif