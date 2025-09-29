/*******************************************
 * Connection.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#pragma once

#include <cstdint>
#include "Result.h"
// #include "rtcconf.h"

enum class ConnectionType
{
    SERIALUSB = 0x11,
    SERIAL1 = 0x01,
    SERIAL2 = 0x02,
    SERIAL3 = 0x03,
    ETHERTCP = 0x04,
};

namespace ssr::rtno
{

    struct ConnectionProfile
    {
        ConnectionType connection_type;

        // #ifdef USE_ETHERNET_CONNECTION
        uint8_t *mac_address;
        uint8_t *ip_address;
        uint8_t *default_gateway;
        uint8_t *subnet_mask;
        uint16_t port;
        // #endif

        // #ifdef USE_UART_CONNECTION
        uint16_t baudrate;
        // #endif
    };

    RESULT
    Connection_setup(const ConnectionProfile &connection_profile);
}