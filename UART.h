#pragma once

#include "SerialDevice.h"

namespace ssr::rtno {
    RESULT UART_init(unsigned char num, unsigned long baudrate);
    RESULT UART_putc(const uint8_t c);
    RESULT UART_available();
    RESULT UART_getc(uint8_t* c);
}