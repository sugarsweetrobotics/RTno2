#ifndef RTNO_HEADER_INCLUDED
#define RTNO_HEADER_INCLUDED

/*******************************************
 * RTno.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#define USE_UART_CONNECTION
// #define USE_ETHERNET_CONNECTION
// #define USE_TIMER1_EC
// #define USE_TIMERONE_EC
#define USE_FSPTIMER_EC

#include "Arduino.h"
#include "RTC/BasicDataType.h"
#include "RTC/InPort.h"
#include "RTC/OutPort.h"
#include "RTC/rtcconf.h"
#include "rtno/Logger.h"

#ifdef USE_UART_CONNECTION
#include "hal/UART.h"
#endif

#ifdef USE_ETHERNET_CONNECTION
#include "EtherTcp.h"
#include "EthernetInterface.h"
#endif

#include "ec/Timer1ExecutionContext.h"
#include "ec/TimerOneExecutionContext.h"
#include "ec/MainLoopExecutionContext.h"
#include "ec/FSPTimerExecutionContext.h"

#include "ec/ProxySyncEC.h"

// global variables for rtcconf
// extern volatile exec_cxt_str exec_cxt;
// extern config_str conf;

int RTnoProfile_addInPort(PortBase *port);
int RTnoProfile_addOutPort(PortBase *port);

// global functions
// RTno APIs
void rtcconf(config_t &conf, exec_cxt_t &exec_cxt);

inline void addInPort(InPortBase &inPort)
{
  RTnoProfile_addInPort(&inPort);
}

inline void addOutPort(OutPortBase &outPort)
{
  RTnoProfile_addOutPort(&outPort);
}

void RTno_setup(int (*on_initialize)(), int (*on_activated)(), int (*on_deactivated)(), int (*on_execute)(), int (*on_error)(), int (*on_reset)());
void RTno_loop();

#if !defined(RTNO_NOT_MAIN)

int onInitialize();
int onActivated();
int onDeactivated();
int onExecute();
int onError();
int onReset();

//////////////////////////////////////////
// DO NOT MODIFY THESE FUNCTIONS
//////////////////////////////////////////
void setup()
{
  RTno_setup(onInitialize, onActivated, onDeactivated, onExecute, onError, onReset);
}

//////////////////////////////////////////
// DO NOT MODIFY THESE FUNCTIONS
//////////////////////////////////////////
void loop()
{
  RTno_loop();
}

#endif

extern Logger logger;

#define RTNO_LOG(FMT) logger.print(FMT "\n")
// #define RTNO_LOG(FMT, ...) logger.print(FMT "\n", __VA_ARGS__)

#define RTNO_LOGGER logger
#endif
