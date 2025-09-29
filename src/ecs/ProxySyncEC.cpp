/*******************************************
 * ProxySyncEC.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#include "ProxySyncEC.h"

namespace ssr::rtno
{
  void ProxySyncEC_start() {}
  void ProxySyncEC_resume() {}
  void ProxySyncEC_suspend() {}

  void ProxySyncEC_init()
  {
    ssr::rtno::EC_init(0x21);

    ssr::rtno::EC_start = ProxySyncEC_start;
    ssr::rtno::EC_suspend = ProxySyncEC_suspend;
    ssr::rtno::EC_resume = ProxySyncEC_resume;
  }

}