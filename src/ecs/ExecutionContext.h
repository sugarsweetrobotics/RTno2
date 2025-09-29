/*******************************************
 * ExecutionContext.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#pragma once

#include <stdint.h>
#include "RTC/rtcconf.h"

namespace ssr::rtno
{
    typedef int8_t LifeCycleState;
    typedef int8_t ReturnValue_t;

    void EC_init(int8_t);
    LifeCycleState EC_get_component_state();
    ReturnValue_t EC_activate_component();
    ReturnValue_t EC_deactivate_component();
    ReturnValue_t EC_execute();
    ReturnValue_t EC_error();
    ReturnValue_t EC_fault();
    int8_t EC_get_type();

    extern void (*EC_start)();
    extern void (*EC_suspend)();
    extern void (*EC_resume)();

    void EC_setup(exec_cxt_str &exec_cxt, int (*on_activated)(), int (*on_deactivated)(), int (*on_execute)(), int (*on_error)(), int (*on_reset)());
}
