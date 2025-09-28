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
#include "BasicDataType.h"
#include "InPort.h"
#include "OutPort.h"
#include "Logger.h"
#include "rtcconf.h"

#ifdef USE_UART_CONNECTION
#include "UART.h"
#endif

#ifdef USE_ETHERNET_CONNECTION
#include "EtherTcp.h"
#include "EthernetInterface.h"
#endif

#ifdef USE_TIMER1_EC
#include "Timer1ExecutionContext.h"
#endif

#include "TimerOneExecutionContext.h"

#include "FSPTimerExecutionContext.h"

#include "ProxySyncEC.h"

// global variables for rtcconf
// extern volatile exec_cxt_str exec_cxt;
// extern config_str conf;

int RTnoProfile_addInPort(PortBase *port);
int RTnoProfile_addOutPort(PortBase *port);

// global functions
// RTno APIs
// extern "C" {
void rtcconf(config_str &conf, exec_cxt_str &exec_cxt);
//};

// class DataFlowComponentBase {
// public:

// public:
//   DataFlowComponentBase() {}
//   virtual ~DataFlowComponentBase() {}

// public:
//   virtual int onInitialize() {
//     return RTC_OK;
//   }

//   /**
//    * onActivated()
//    * This function is called when RTno is activated only if RTno is RTC_INACTIVE condition.
//    * RTno is usually activated by RT System Editor or other tools for OpenRTM-aist.
//    */
//   virtual int onActivated() {
//     return RTC_OK;
//   }

//   /**
//    * onExecute()
//    * This function is periodically called when the RTno-proxy is RTC_ACTIVE condition.
//    */
//   virtual int onExecute() {
//     return RTC_OK;
//   }

//   /**
//    * onDeactivated()
//    * This function is called when RTno is deactivated only if RTno is RTC_ACTIVE condition.
//    * RTno is usually deactivated by RT System Editor or other tools for OpenRTM-aist.
//    */
//   virtual int onDeactivated() {
//     return RTC_OK;
//   }

//   /**
//    * onError
//    * This function is called when RTno is error only if RTno is in RTC_ERROR condition.
//    * [DANGEROUS] This function is periodically called in very short interval.
//    */
//   virtual int onError() {
//     return RTC_OK;
//   }

//   /**
//    * onReset
//    * This function is called when RTno is reset only if RTno is in RTC_ERROR condition.
//    * RTno is usually reset by RT System Editor or other tools for OpenRTM-aist.
//    */
//   virtual int onReset() {
//     return RTC_OK;
//   }

// protected:

//   void addInPort(InPortBase& inPort) {
//     RTnoProfile_addInPort(&inPort);
//   }

//   void addOutPort(OutPortBase& outPort) {
//     RTnoProfile_addOutPort(&outPort);
//   }

// };

inline void addInPort(InPortBase &inPort)
{
  RTnoProfile_addInPort(&inPort);
}

inline void addOutPort(OutPortBase &outPort)
{
  RTnoProfile_addOutPort(&outPort);
}

void RTno_setup(int (*on_initialize)(), int (*on_activated)(), int (*on_deactivated)(), int (*on_execute)(), int (*on_error)(), int (*on_reset)());
// void RTno_setup(DataFlowComponentBase* rtc);
void RTno_loop();

extern Logger logger;

#define RTNO_LOG(FMT) logger.print(FMT "\n")
// #define RTNO_LOG(FMT, ...) logger.print(FMT "\n", __VA_ARGS__)

#define RTNO_LOGGER logger
#endif

// #endif
