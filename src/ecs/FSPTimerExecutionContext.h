/*******************************************
 * FSPTimerExecutionContext.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/

#pragma once

#if defined(__arm__)

#include "ecs/ExecutionContext.h"

namespace ssr::rtno
{
    void FSPTimerEC_init(double microsecond);
}
#endif
