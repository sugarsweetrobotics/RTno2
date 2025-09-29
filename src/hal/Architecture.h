#pragma once

/*******************************************
 * Architecture.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#include <cstdint>

namespace ssr::rtno
{
    enum class Architecture : uint8_t
    {
        AVR = 1,
        ARM = 2,
        UNKNOWN = 255,
    };

    inline Architecture getArchitecture()
    {
#if defined(__AVR__)
        return Architecture::AVR;
#elif defined(__arm__)
        return Architecture::ARM;
#else
        return Architecture::UNKNOWN;
#endif
    }

} // namespace ssr::rtno