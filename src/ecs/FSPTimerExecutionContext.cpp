/*******************************************
 * FSPTimerExecutionContext.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#if defined(__arm__)

#include <stdint.h>

#include <Arduino.h>
#include "comm/Packet.h"
#include "ecs/FSPTimerExecutionContext.h"

#include <FspTimer.h>

namespace ssr::rtno
{
  FspTimer *_timer;

  static int32_t m_Period;
  static bool m_Suspend = 0;
  static ReturnValue_t FSPTimerEC_returnValue;

  void FSPTimerEC_start();
  void FSPTimerEC_suspend();
  void FSPTimerEC_resume();

  void FSPTimerEC_execute(timer_callback_args_t *arg)
  {
    if (!m_Suspend)
    {
      FSPTimerEC_returnValue = EC_execute();
    }
  }

  void FSPTimerEC_init(double rate)
  {
    EC_init(0x24);

    _timer = new FspTimer();

    uint8_t type;
    int8_t timer_ch = FspTimer::get_available_timer(type);
    if (timer_ch < 0)
    {
      EC_fault();
      return;
    }
    _timer->begin(TIMER_MODE_PERIODIC, type, static_cast<uint8_t>(timer_ch), (float)rate, 0.0f, FSPTimerEC_execute, nullptr);

    EC_start = FSPTimerEC_start;
    EC_suspend = FSPTimerEC_suspend;
    EC_resume = FSPTimerEC_resume;
  }

  void FSPTimerEC_start()
  {
    _timer->setup_overflow_irq();
    _timer->open();
    _timer->start();
  }

  void FSPTimerEC_suspend()
  {
    m_Suspend = true;
  }

  void FSPTimerEC_resume()
  {
    m_Suspend = false;
  }

}
#endif