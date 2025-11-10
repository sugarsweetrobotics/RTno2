/*******************************************
 * MainLoopEC.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#pragma once

#include "ec/ExecutionContext.h"

void MainLoopEC_init(double rate);
void MainLoopEC_svc();

#if defined USE_MAINLOOP_EC

#include "hal/DurationClock.h"
#include "rtno/Packet.h"
static uint32_t interval_ms;
static uint32_t last_exec_time_ms = 0;
void MainLoopEC_start() {}
void MainLoopEC_resume() {}
void MainLoopEC_suspend() {}

void MainLoopEC_init(double rate)
{
  EC_init(ECType::MAINLOOP);

  EC_start = MainLoopEC_start;
  EC_suspend = MainLoopEC_suspend;
  EC_resume = MainLoopEC_resume;

  interval_ms = (uint32_t)(1.0 / rate) * 1000;
  last_exec_time_ms = DurationClock_now_ms();
}

void MainLoopEC_svc()
{
  duration_t duration = DurationClock_now_ms() - last_exec_time_ms;
  if (duration >= interval_ms)
  {
    if (EC_get_component_state() == RTC_STATE_ACTIVE)
    {
      EC_execute();
      last_exec_time_ms = DurationClock_now_ms();
    }
  }
}

#endif // USE_MAINLOOP_EC