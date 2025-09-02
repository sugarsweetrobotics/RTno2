#include "Arduino.h"
#include "SerialDevice.h"

namespace ssr::rtno {

RESULT (*SerialDevice_available)();
RESULT (*SerialDevice_putc)(const uint8_t c);
RESULT (*SerialDevice_getc)(uint8_t* c);

RESULT SerialDevice_read(uint8_t* buffer, const uint8_t size, uint8_t* size_read, const duration_t& wait_usec)
{
  *size_read = 0;
  DurationClock_tick();
  for(uint8_t i = 0;i < size;i++) {
    while (1) {
      if (SerialDevice_available() == RESULT::OK) {
        break;
      }
      
      if (wait_usec != INFINITE && DurationClock_tack() >= wait_usec) {
        return RESULT::TIMEOUT;
      }
    }

    RESULT result = SerialDevice_getc(buffer + i);
    if (result != RESULT::OK) {
      return result;
    }
    (*size_read)++;
  }
  return RESULT::OK;
}

} // namespace ssr::rtno
