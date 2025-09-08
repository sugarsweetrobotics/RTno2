#ifndef TIMERONE_EXECUTION_CONTEXT
#define TIMERONE_EXECUTION_CONTEXT

#include "ExecutionContext.h"

void TimerOneEC_start();
void TimerOneEC_suspend();
void TimerOneEC_resume();
void TimerOneEC_init(double rate);

#ifndef RTNO_SUBMODULE_DEFINE

#ifdef TimerOne_h_
static int32_t m_Period;
static bool m_Suspend = 0;
static ReturnValue_t TimerOneEC_returnValue;

static void TimerOneEC_execute() {
    if (m_Suspend) {
        TimerOneEC_returnValue = EC_execute();
    }
}

#endif

void TimerOneEC_init(double rate)
{
  EC_init(0x25);
  #ifdef TimerOne_h_
  m_Period = (int32_t)(1000000 / rate);

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
  Timer1.initialize(m_Period); //5秒待機
  Timer1.attachInterrupt(TimerOneEC_execute);
  #endif
}

void TimerOneEC_suspend()
{
  #ifdef TimerOne_h_
    m_Suspend = true;
    #endif
}

void TimerOneEC_resume()
{

  #ifdef TimerOne_h_
    m_Suspend = false;
    #endif
}


#endif

#endif