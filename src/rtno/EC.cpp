#define RTNO_NOT_MAIN
#define __THIS_IS_NOT_MAIN__
#include <stdint.h>
#include "rtno/Packet.h"
#include "RTno2.h"
#include "rtno/Transport.h"
#include "rtno/RTnoProfile.h"

#include "Arduino.h"

using namespace ssr::rtno;

static ECType m_ECType;
static LifeCycleState m_Condition;

extern int (*RTno_onInitialize)();
extern int (*RTno_onActivated)();
extern int (*RTno_onDeactivated)();
extern int (*RTno_onExecute)();
extern int (*RTno_onError)();
extern int (*RTno_onReset)();

void EC_init(ECType Type)
{
    m_ECType = Type;
    m_Condition = RTC_STATE_INACTIVE;
}

ECType EC_get_type()
{
    return m_ECType;
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
    // digitalWrite(LED_BUILTIN, HIGH);
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

void EC_setup(exec_cxt_t &exec_cxt)
{
    switch (exec_cxt.periodic.type)
    {
// #ifdef USE_TIMER1_EC
//   case Timer1ExecutionContext:
//     Timer1EC_init(exec_cxt.periodic.rate);
//     break;
// #endif // USE_TIMER1_EC
//   case ProxySynchronousExecutionContext:
#if defined(__AVR__)
    case ECType::TIMERONE:
        TimerOneEC_init(exec_cxt.periodic.rate);
        break;
    case ECType::TIMER1:
        Timer1EC_init(exec_cxt.periodic.rate);
        break;
#endif
#if defined(__arm__)
    case ECType::FSPTIMER:
        FSPTimerEC_init(exec_cxt.periodic.rate);
        break;
#endif
    case ECType::MAINLOOP:
        MainLoopEC_init(exec_cxt.periodic.rate);
        break;
    default:
        ProxySyncEC_init();
        break;
    }
}
