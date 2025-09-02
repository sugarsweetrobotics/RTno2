#ifndef SERIAL_DEVICE_HEADER_INCLUDED
#define SERIAL_DEVICE_HEADER_INCLUDED

#include <stdint.h>

#include "Result.h"
#include "DurationClock.h"

namespace ssr::rtno {
    // Write single char to Serial Device
    // This function is initialized in the initialization sequence.
    extern RESULT (*SerialDevice_putc)(const uint8_t c);

    // Check Single char is avalable to read.
    // If available, returns RESULT::OK.
    // This function is initialized in the initialization sequence.
    extern RESULT (*SerialDevice_available)();

    // Read single char from Serial Device.
    // Read data is written to argument c
    // This function is initialized in the initialization sequence.
    extern RESULT (*SerialDevice_getc)(uint8_t* c);

    // Read multiple block
    // This function uses SerialDevice_available and SerialDevice_getc
    // buffer: written buffer.
    // buffer_size: max size of buffer.
    // size_read: written size.
    // duration_t: max time of read. If exceeded, returns RESULT::TIMEOUT.
    RESULT SerialDevice_read(uint8_t* buffer, const uint8_t buffer_size, uint8_t* size_read, const duration_t& wait_usec);
}
#endif
