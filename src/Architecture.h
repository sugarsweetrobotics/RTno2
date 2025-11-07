#pragma once

/*******************************************
 * Architecture.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#include <stdint.h>

namespace ssr::rtno
{
    enum class Architecture : uint8_t
    {
        ARCH_AVR = 1,
        ARCH_ARM = 2,
        ARCH_UNKNOWN = 255,
    };

    inline Architecture getArchitecture()
    {
#if defined(__AVR__)
        return Architecture::ARCH_AVR;
#elif defined(__arm__)
        return Architecture::ARCH_ARM;
#else
        return Architecture::ARCH_UNKNOWN;
#endif
    }

} // namespace ssr::rtno