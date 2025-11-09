#ifndef DURATION_CLOCK_HEADER_FILE_INCLUDED
#define DURATION_CLOCK_HEADER_FILE_INCLUDED

#include <stdint.h>

namespace ssr::rtno {
    using duration_t = uint8_t;
    static const duration_t INFINITE = 0xFF;
    
    void DurationClock_tick();
    duration_t DurationClock_tack();
}

#endif