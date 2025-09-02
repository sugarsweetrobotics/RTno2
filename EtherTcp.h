#ifndef ETHER_TCP_HEADER_INCLUDED
#define ETHER_TCP_HEADER_INCLUDED


#include <stdint.h>
#include "SerialDevice.h"

namespace ssr::rtno {
    RESULT EtherTcp_init(uint8_t* mac, uint8_t *ip, uint8_t *gateway, uint8_t *subnet, uint16_t port);

    RESULT EtherTcp_putc(const uint8_t c);
    RESULT EtherTcp_available();
    RESULT EtherTcp_getc(uint8_t* c);
}
#endif // #ifndef ETHER_HEADER_INCLUDED
