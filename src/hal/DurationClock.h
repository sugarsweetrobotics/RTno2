/*******************************************
 * DurationClock.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/

#pragma once
#include <stdint.h>

namespace ssr::rtno
{
    using duration_t = uint8_t;
    static const duration_t INFINITE = 0xFF;

    void DurationClock_tick();
    duration_t DurationClock_tack();
}