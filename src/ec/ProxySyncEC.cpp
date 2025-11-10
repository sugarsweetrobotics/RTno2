#include "ProxySyncEC.h"
#include <RTC/rtcconf.h>
void ProxySyncEC_start() {}
void ProxySyncEC_resume() {}
void ProxySyncEC_suspend() {}

void ProxySyncEC_init()
{
  EC_init(ECType::PROXY_SYNCHRONOUS);

  EC_start = ProxySyncEC_start;
  EC_suspend = ProxySyncEC_suspend;
  EC_resume = ProxySyncEC_resume;
}
