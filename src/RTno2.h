/*******************************************
 * RTno2.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#ifndef RTNO_HEADER_INCLUDED
#define RTNO_HEADER_INCLUDED

#define USE_UART_CONNECTION
// #define USE_ETHERNET_CONNECTION
// #define USE_TIMER1_EC
// #define USE_TIMERONE_EC
#define USE_FSPTIMER_EC

#include "Arduino.h"

#include "Logger.h"
#include "RTC/BasicDataType.h"
#include "RTC/InPort.h"
#include "RTC/OutPort.h"
#include "RTC/rtcconf.h"
#include "ecs/ProxySyncEC.h"

#ifdef USE_TIMERONE_EC
#include "TimerOneExecutionContext.h"
#endif

/**
 * This function must be called at first.
 * conf._default.baudrate: baudrate of serial communication
 * exec_cxt.periodic.type: reserved but not used.
 */
void rtcconf(config_str &conf, exec_cxt_str &exec_cxt);

void addInPort(InPortBase &inPort);
void addOutPort(OutPortBase &outPort);

void RTno_setup(int (*on_initialize)(), int (*on_activated)(), int (*on_deactivated)(), int (*on_execute)(), int (*on_error)(), int (*on_reset)());
void RTno_loop();

extern Logger logger;

#define RTNO_LOG(FMT) logger.print(FMT "\n")
// #define RTNO_LOG(FMT, ...) logger.print(FMT "\n", __VA_ARGS__)
#define RTNO_LOGGER logger

#endif
