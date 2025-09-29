/*******************************************
 * DurationClock.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#include "DurationClock.h"

#include <Arduino.h>

namespace ssr::rtno
{

    static duration_t start_time;

    void DurationClock_tick()
    {
        start_time = millis();
    }

    duration_t DurationClock_tack()
    {
        return millis() - start_time;
    }

} // namespace ssr::rtno