#ifndef TIMERONE_EXECUTION_CONTEXT
#define TIMERONE_EXECUTION_CONTEXT

#include "ExecutionContext.h"

void TimerOneEC_init(double rate);

#ifdef TimerOne_h_

void TimerOneEC_start();
void TimerOneEC_suspend();
void TimerOneEC_resume();
static int32_t m_TimerOnePeriod;
static bool m_TimerOneSuspend = 0;
static ReturnValue_t TimerOneEC_returnValue;

inline void TimerOneEC_execute()
{
  if (!m_TimerOneSuspend)
  {
    TimerOneEC_returnValue = EC_execute();
  }
}

void TimerOneEC_init(double rate)
{
  EC_init(0x25);
#ifdef TimerOne_h_
  m_TimerOnePeriod = (int32_t)(1000000 / rate);
  m_TimerOneSuspend = false;
  EC_start = TimerOneEC_start;
  EC_suspend = TimerOneEC_suspend;
  EC_resume = TimerOneEC_resume;
#else
  EC_fault();
#endif
}

void TimerOneEC_start()
{
#ifdef TimerOne_h_
  Timer1.initialize(m_TimerOnePeriod); // 5秒待機
  Timer1.attachInterrupt(TimerOneEC_execute);
#endif
}

inline void TimerOneEC_suspend()
{
#ifdef TimerOne_h_
  m_TimerOneSuspend = true;
#endif
}

inline void TimerOneEC_resume()
{

#ifdef TimerOne_h_
  m_TimerOneSuspend = false;
#endif
}

#endif // TimerOne_h_

#endif
