#ifndef DURATION_CLOCK_HEADER_FILE_INCLUDED
#define DURATION_CLOCK_HEADER_FILE_INCLUDED

#include <stdint.h>

namespace ssr::rtno {
    using duration_t = uint32_t;
    static const duration_t INFINITE = 0xFFFFFFFF;
    
    void DurationClock_tick();
    duration_t DurationClock_tack();
}

#endif