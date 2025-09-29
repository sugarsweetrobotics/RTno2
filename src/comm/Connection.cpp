/*******************************************
 * Connection.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#include "comm/Connection.h"

#include "hal/UART.h"
#include "hal/EtherTcp.h"

namespace ssr::rtno
{
    RESULT Connection_setup(const ConnectionProfile &connection_profile)
    {
        switch (connection_profile.connection_type)
        {
        case ConnectionType::ETHERTCP:
            EtherTcp_init(
                connection_profile.mac_address,
                connection_profile.ip_address,
                connection_profile.default_gateway,
                connection_profile.subnet_mask,
                connection_profile.port);
            break;
        case ConnectionType::SERIALUSB:
            UART_init(0, connection_profile.baudrate);
            break;
        case ConnectionType::SERIAL1:
            UART_init(1, connection_profile.baudrate);
            break;
        case ConnectionType::SERIAL2:
            UART_init(2, connection_profile.baudrate);
            break;
        case ConnectionType::SERIAL3:
            UART_init(3, connection_profile.baudrate);
            break;
        default:
            break;
        }

        return RESULT::OK;
    }

}