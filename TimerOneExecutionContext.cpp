#define RTNO_SUBMODULE_DEFINE

#include <stdint.h>
#include <Arduino.h>
#include "RTno.h"
#include "Packet.h"
#include "TimerOneExecutionContext.h"
//#include <avr/io.h>
//#include <avr/interrupt.h>

#ifdef USE_TIMEONE_EC

#include <TimerOne.h>

static int32_t m_Period;
static bool m_Suspend = 0;
static ReturnValue_t TimerOneEC_returnValue;

void TimerOneEC_start();
void TimerOneEC_suspend();
void TimerOneEC_resume();

void TimerOneEC_execute() {
    if (m_Suspend) {
        TimerOneEC_returnValue = EC_execute();
    }
}


void TimerOneEC_init(double rate)
{
  EC_init(0x22);
  m_Period = (int32_t)(1000000 / rate);

  EC_start = TimerOneEC_start;
  EC_suspend = TimerOneEC_suspend;
  EC_resume = TimerOneEC_resume;
}

void TimerOneEC_start()
{
  Timer1.initialize(m_Period); //5秒待機
  Timer1.attachInterrupt(TimerOneEC_execute);
}

void TimerOneEC_suspend()
{
    m_Suspend = true;
}

void TimerOneEC_resume()
{
    m_Suspend = false;
}


#endif // USE_TIMERONE_EC