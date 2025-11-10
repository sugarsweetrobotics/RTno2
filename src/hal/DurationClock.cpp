#include "DurationClock.h"

#include <Arduino.h>

static duration_t start_time;

void DurationClock_tick()
{
    start_time = millis();
}

duration_t DurationClock_tack()
{
    return (duration_t)(millis()) - start_time;
}

time_t DurationClock_now_ms()
{
    return millis();
}