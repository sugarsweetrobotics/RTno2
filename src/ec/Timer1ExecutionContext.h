#ifndef TIMER1_EXECUTION_CONTEXT
#define TIMER1_EXECUTION_CONTEXT

#include "ExecutionContext.h"

void Timer1EC_init(double microsecond);

#ifdef USE_TIMER1_EC
static int32_t m_Timer1Period;
static uint8_t m_Timer1ClockSetting;

void Timer1EC_start()
{

    char SREG_buf = SREG;
    cli();
    ICR1 = m_Timer1Period;
    SREG = SREG_buf;

    TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
    TCCR1B |= m_Timer1ClockSetting;

    TIMSK1 = _BV(TOIE1);
    TCCR1B |= m_Timer1ClockSetting;
}

void Timer1EC_suspend()
{
    TIMSK1 &= ~_BV(TOIE1);
}

void Timer1EC_resume()
{
    TIMSK1 = _BV(TOIE1);
    TCCR1B |= m_Timer1ClockSetting;
}

void Timer1EC_init(double microsecond)
{
    EC_init(0x22);
    TCCR1A = 0;
    TCCR1B = _BV(WGM13);

    // Initialize Period

    m_Timer1Period = (F_CPU / 2000000) * (int32_t)(1000000 / microsecond);
    const int32_t maxTimer = 65536;
    if (m_Timer1Period < maxTimer)
    {
        m_Timer1ClockSetting = _BV(CS10);
    }
    else if ((m_Timer1Period /= 8) < maxTimer)
    {
        m_Timer1ClockSetting = _BV(CS11);
    }
    else if ((m_Timer1Period /= 64) < maxTimer)
    {
        m_Timer1ClockSetting = _BV(CS11) | _BV(CS10);
    }
    else if ((m_Timer1Period /= 256) < maxTimer)
    {
        m_Timer1ClockSetting = _BV(CS12);
    }
    else if ((m_Timer1Period /= 1024) < maxTimer)
    {
        m_Timer1ClockSetting = _BV(CS12) | _BV(CS10);
    }
    else
    {
        m_Timer1Period = 0xFFFF, m_Timer1ClockSetting = _BV(CS12) | _BV(CS10);
    }

    EC_start = Timer1EC_start;
    EC_suspend = Timer1EC_suspend;
    EC_resume = Timer1EC_resume;
}

#endif // USE_TIMER1_EC

#endif
