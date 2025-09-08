#include "DurationClock.h"

#include <Arduino.h>

namespace ssr::rtno {

static duration_t start_time;

void DurationClock_tick() {
    start_time = millis();
}

duration_t DurationClock_tack() {
    return millis() - start_time;
}

} // namespace ssr::rtno