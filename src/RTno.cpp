/*******************************************
 * RTno.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/
#include <stdint.h>

#define __THIS_IS_NOT_MAIN__
#include "RTno2.h"

#include "comm/Packet.h"
#include "comm/Transport.h"
#include "comm/Connection.h"
#include "comm/CommandHandler.h"
#include "RTnoProfile.h"
#include "hal/UART.h"

#include "Arduino.h"

using namespace ssr::rtno;

/**
 * Arduino Setup Routine.
 * This function is called when arduino device is turned on.
 */
void RTno_setup(int (*on_initialize)(), int (*on_activated)(), int (*on_deactivated)(), int (*on_execute)(), int (*on_error)(), int (*on_reset)())
{
  RTnoProfile_init(getArchitecture());

  exec_cxt_str *exec_cxt = (exec_cxt_str *)malloc(sizeof(exec_cxt_str));
  config_str *conf = (config_str *)malloc(sizeof(config_str));
  rtcconf(*conf, *exec_cxt);
  if (on_initialize() == RTC_OK)
  {
    EC_setup(*exec_cxt, on_activated, on_deactivated, on_execute, on_error, on_reset);
    Connection_setup(into(conf->_default));
    free(exec_cxt);
    free(conf);
    Transport_init();
    EC_start();
  }
  return;
}

static uint8_t m_pPacketBuffer[PACKET_BUFFER_SIZE];

void RTno_loop()
{
  if (ReceiveCommand(m_pPacketBuffer))
  {
    CommandHandler_handle(m_pPacketBuffer);
  }
}

/**
 * Private Function Definitions
 *
 */

void addInPort(InPortBase &inPort)
{
  RTnoProfile_addInPort(&inPort);
}

void addOutPort(OutPortBase &outPort)
{
  RTnoProfile_addOutPort(&outPort);
}