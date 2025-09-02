#ifndef RTNO_HEADER_INCLUDED
#define RTNO_HEADER_INCLUDED

/*******************************************
 * RTno.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#define RTC_OK 0
#define RTC_ERROR -1
#define RTC_PRECONDITION_NOT_MET -2


#define USE_UART_CONNECTION
// #define USE_ETHERNET_CONNECTION
// #define USE_TIMER1_EC
// #define USE_TIMERONE_EC
#define USE_FSPTIMER_EC

#include "Arduino.h"
#include "BasicDataType.h"
#include "InPort.h"
#include "OutPort.h"
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

#ifdef USE_TIMERONE_EC
#include "TimerOneExecutionContext.h"
#endif

#ifdef USE_FSPTIMER_EC
#include "FSPTimerExecutionContext.h"
#endif


#include "ProxySyncEC.h"
#define PACKET_BUFFER_SIZE 128

#define MAX_PORT 8


// global variables for rtcconf
//extern volatile exec_cxt_str exec_cxt;
//extern config_str conf;

// global functions
// RTno APIs
extern "C" {
  void rtcconf(config_str& conf, exec_cxt_str& exec_cxt);
};

extern "C" {
  void addInPort(InPortBase& inPort);
  void addOutPort(OutPortBase& outPort);
}


class DataFlowComponentBase {

public:
  DataFlowComponentBase() {}
  virtual ~DataFlowComponentBase() {}

public:
  virtual int onInitialize() {
    return RTC_OK;
  }


  /**
   * onActivated()
   * This function is called when RTno is activated only if RTno is RTC_INACTIVE condition.
   * RTno is usually activated by RT System Editor or other tools for OpenRTM-aist.
   */
  virtual int onActivated() {
    return RTC_OK;
  }

  /**
   * onExecute()
   * This function is periodically called when the RTno-proxy is RTC_ACTIVE condition.
   */
  virtual int onExecute() {
    return RTC_OK;
  }

  /**
   * onDeactivated()
   * This function is called when RTno is deactivated only if RTno is RTC_ACTIVE condition.
   * RTno is usually deactivated by RT System Editor or other tools for OpenRTM-aist.
   */
  virtual int onDeactivated() {
    return RTC_OK;
  }

  /**
   * onError
   * This function is called when RTno is error only if RTno is in RTC_ERROR condition.
   * [DANGEROUS] This function is periodically called in very short interval.
   */ 
  virtual int onError() {
    return RTC_OK;
  }

  /**
   * onReset
   * This function is called when RTno is reset only if RTno is in RTC_ERROR condition.
   * RTno is usually reset by RT System Editor or other tools for OpenRTM-aist.
   */
  virtual int onReset() {
    return RTC_OK;
  }

protected:

  void addInPort(InPortBase& inPort) {
    ::addInPort(inPort);
  }

  void addOutPort(OutPortBase& outPort) {
    ::addOutPort(outPort);
  }

};

void RTno_setup(DataFlowComponentBase* rtc);
void RTno_loop();
#endif