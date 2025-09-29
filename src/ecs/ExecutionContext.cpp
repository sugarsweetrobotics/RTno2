/*******************************************
 * ExecutionContext.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#define RTNO_SUBMODULE_DEFINE

#include <stdint.h>

#include "comm/Packet.h"

#include "ExecutionContext.h"

#include "ecs/FSPTimerExecutionContext.h"
#include "ecs/ProxySyncEC.h"

class DataFlowComponentBase;

int (*RTno_onActivated)();
int (*RTno_onDeactivated)();
int (*RTno_onExecute)();
int (*RTno_onError)();
int (*RTno_onReset)();

namespace ssr::rtno
{
    // static int8_t m_Type;
    // static LifeCycleState m_Condition;

    void (*EC_start)();
    void (*EC_resume)();
    void (*EC_suspend)();

    static int8_t m_Type = 0;
    static LifeCycleState m_Condition;

    void EC_setup(exec_cxt_str &exec_cxt, int (*on_activated)(), int (*on_deactivated)(), int (*on_execute)(), int (*on_error)(), int (*on_reset)())
    {
        RTno_onActivated = on_activated;
        RTno_onDeactivated = on_deactivated;
        RTno_onExecute = on_execute;
        RTno_onReset = on_reset;
        RTno_onError = on_error;
        switch (exec_cxt.periodic.type)
        {
// #ifdef USE_TIMER1_EC
//   case Timer1ExecutionContext:
//     Timer1EC_init(exec_cxt.periodic.rate);
//     break;
// #endif // USE_TIMER1_EC
//   case ProxySynchronousExecutionContext:
#if defined(__AVR__)
        case FSPTimerExecutionContext:
            TimerOneEC_init(exec_cxt.periodic.rate);
            break;
#endif
#if defined(__arm__)
        case FSPTimerExecutionContext:
            FSPTimerEC_init(exec_cxt.periodic.rate);
            break;
#endif
        default:
            ProxySyncEC_init();
            break;
        }
    }

    void EC_init(int8_t Type)
    {
        m_Type = Type;
        m_Condition = RTC_STATE_INACTIVE;
    }

    int8_t EC_get_type()
    {
        return m_Type;
    }

    LifeCycleState EC_get_component_state()
    {
        return m_Condition;
    }

    ReturnValue_t EC_activate_component()
    {
        if (m_Condition != RTC_STATE_INACTIVE)
        {
            return RTC_PRECONDITION_NOT_MET;
        }

        // if(__rtc->onActivated() == RTC_OK) {
        if (RTno_onActivated() == RTC_OK)
        {
            m_Condition = RTC_STATE_ACTIVE;
            return RTC_OK;
        }

        m_Condition = RTC_STATE_ERROR;
        return RTC_ERROR;
    }

    ReturnValue_t EC_fault()
    {
        m_Condition = RTC_STATE_ERROR;
        return RTC_OK;
    }

    ReturnValue_t EC_deactivate_component()
    {
        if (m_Condition != RTC_STATE_ACTIVE)
        {
            return RTC_PRECONDITION_NOT_MET;
        }

        // if(__rtc->onDeactivated() == RTC_OK) {
        if (RTno_onDeactivated() == RTC_OK)
        {
            m_Condition = RTC_STATE_INACTIVE;
            return RTC_OK;
        }
        else
        {
            m_Condition = RTC_STATE_ERROR;
            return RTC_ERROR;
        }
    }

    ReturnValue_t EC_execute()
    {
        if (m_Condition != RTC_STATE_ACTIVE)
        {
            return RTC_PRECONDITION_NOT_MET;
        }

        // if(__rtc->onExecute() == RTC_OK) {
        if (RTno_onExecute() == RTC_OK)
        {
            return RTC_OK;
        }
        else
        {
            m_Condition = RTC_STATE_ERROR;
            return RTC_ERROR;
        }
    }

}