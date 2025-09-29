#ifndef RTC_CONF_HEADER_INCLUDED
#define RTC_CONF_HEADER_INCLUDED

#include <cstdint>

#include "comm/Connection.h"

#define RTC_OK 0
#define RTC_ERROR -1
#define RTC_PRECONDITION_NOT_MET -2

#ifdef USE_ETHERNET_CONNECTION

#define IPaddr(a1, a2, a3, a4) \
  ((((uint32_t)a4) << 24) | (((uint32_t)a3) << 16) | (((uint32_t)a2) << 8) | (((uint32_t)a1) << 0))

#define MACaddr(a1, a2, a3, a4, a5, a6) \
  ((((uint64_t)a6) << 40) | (((uint64_t)a5) << 32) | (((uint64_t)a4) << 24) | (((uint64_t)a3) << 16) | (((uint64_t)a2) << 8) | (((uint64_t)a1) << 0))

#endif

struct default_str
{
  // #ifdef USE_ETHERNET_CONNECTION
  uint8_t *mac_address;
  uint16_t port;
  uint8_t *default_gateway;
  uint8_t *ip_address;
  uint8_t *subnet_mask;
  // #endif

  // #ifdef USE_UART_CONNECTION
  uint16_t baudrate;
  // #endif

  ConnectionType connection_type;
};

inline ssr::rtno::ConnectionProfile into(const default_str &conf_)
{
  return ssr::rtno::ConnectionProfile{
      .connection_type = conf_.connection_type,
      .mac_address = conf_.mac_address,
      .ip_address = conf_.ip_address,
      .default_gateway = conf_.default_gateway,
      .subnet_mask = conf_.subnet_mask,
      .port = conf_.port,
      .baudrate = conf_.baudrate,
  };
}

struct ether_str
{
};

struct config_str
{
  struct default_str _default;
};

struct exec_cxt_str
{
  struct periodic_str
  {
    float rate;
    uint8_t type;
  } periodic;
};

#ifdef USE_UART_CONNECTION
#define ConnectionTypeSerialUSB 0x11
#define ConnectionTypeSerial1 0x01
#define ConnectionTypeSerial2 0x02
#define ConnectionTypeSerial3 0x03
#endif

#ifdef USE_ETHERNET_CONNECTION
#define ConnectionTypeEtherTcp 0x04
#endif

#define ProxySynchronousExecutionContext 0x21

#ifdef USE_TIMER1_EC
#define Timer1ExecutionContext 0x22
#endif

#define Timer2ExecutionContext 0x23

#define FSPTimerExecutionContext 0x24

#define TimerOneExecutionContext 0x25

void rtcconf(config_str &conf, exec_cxt_str &exec_cxt);

#endif
