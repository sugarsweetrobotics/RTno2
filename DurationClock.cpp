#include "DurationClock.h"

#include <Arduino.h>

namespace ssr::rtno {

static duration_t start_time;

void DurationClock_tick() {
    start_time = micros();
}

duration_t DurationClock_tack() {
    return micros() - start_time;
}

} // namespace ssr::rtno