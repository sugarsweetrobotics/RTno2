/*******************************************
 * Transport.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#include "Packet.h"
#include "Transport.h"

#include <stdint.h>
#include "Arduino.h"

namespace ssr::rtno
{

  RESULT Transport_init()
  {
    return RESULT::OK;
  }

  RESULT Transport_SendPacket(const COMMAND command, const RESULT packet_result, const uint8_t data_length, const uint8_t *packet_data)
  {
    uint8_t sum = 0;
    RESULT result;
    uint8_t buf = PACKET_STARTING_CHARACTOR_0;
    if ((result = SerialDevice_putc(&buf)) != RESULT::OK)
      return result;
    buf = PACKET_STARTING_CHARACTOR_1;
    if ((result = SerialDevice_putc(&buf)) != RESULT::OK)
      return result;

    if ((result = SerialDevice_putc((uint8_t *)&command)) != RESULT::OK)
      return result;
    sum += (uint8_t)command;

    if ((result = SerialDevice_putc((uint8_t *)&packet_result)) != RESULT::OK)
      return result;
    sum += (uint8_t)packet_result;

    if ((result = SerialDevice_putc((uint8_t *)&data_length)) != RESULT::OK)
      return result;
    sum += data_length;

    for (uint8_t i = 0; i < data_length; i++)
    {
      sum += packet_data[i];
      if ((result = SerialDevice_putc(packet_data + i)) != RESULT::OK)
        return result;
    }
    if ((result = SerialDevice_putc(&sum)) != RESULT::OK)
      return result;
    return RESULT::OK;
  }

  RESULT _Transport_WaitStartPackets(const duration_t &timeout)
  {
    uint8_t buf;
    RESULT ret;
    DurationClock_tick();
    while (1)
    {
      while (1)
      {
        if (timeout != INFINITE && DurationClock_tack() > timeout)
        {
          return RESULT::TIMEOUT;
        }
        if (SerialDevice_available() != RESULT::OK)
        {
          continue;
        }
        if ((ret = SerialDevice_getc(&buf)) != RESULT::OK)
          return ret;
        if (buf == PACKET_STARTING_CHARACTOR_0)
          break;
      }
      while (1)
      {
        if (timeout != INFINITE && DurationClock_tack() > timeout)
          return RESULT::TIMEOUT;

        if (SerialDevice_available() != RESULT::OK)
          continue;
        if ((ret = SerialDevice_getc(&buf)) != RESULT::OK)
          return ret;
        break;
      }
      if (buf == PACKET_STARTING_CHARACTOR_1)
        break;
    }
    return RESULT::OK;
  }

  RESULT Transport_ReceivePacket(uint8_t *packet, uint8_t *size_read, const duration_t &timeout)
  {
    uint8_t counter = 0;
    uint8_t buf;
    RESULT ret;
    uint8_t size_read_local;
    if ((ret = _Transport_WaitStartPackets(timeout)) != RESULT::OK)
    {
      if (ret == RESULT::TIMEOUT)
      {
        return RESULT::PACKET_START_TIMEOUT;
      }
      else
      {
        return ret;
      }
    }
    // DurationClock_tick();
    // while(1) {
    //   while(1) {
    //     if (timeout != INFINITE && DurationClock_tack() > timeout) return RESULT::TIMEOUT;

    //     if (SerialDevice_available() != RESULT::OK) continue;
    //     if((ret=SerialDevice_getc(&buf)) != RESULT::OK) return ret;
    //     if (buf == PACKET_STARTING_CHARACTOR_0) break;
    //   }
    //   while(1) {
    //     if (timeout != INFINITE && DurationClock_tack() > timeout) return RESULT::TIMEOUT;

    //     if (SerialDevice_available() != RESULT::OK) continue;
    //     if((ret=SerialDevice_getc(&buf)) != RESULT::OK) return ret;
    //     break;
    //   }
    //   if (buf == PACKET_STARTING_CHARACTOR_1) break;
    // }
    // Read packet header. Header includes size of data area of packet.
    if ((ret = SerialDevice_read(packet, PACKET_HEADER_SIZE, &size_read_local, timeout)) != RESULT::OK)
    {
      if (ret == RESULT::TIMEOUT)
      {
        return RESULT::PACKET_HEADER_TIMEOUT;
      }
      return ret;
    }
    // Read multiple bytes according to the header.
    if ((ret = SerialDevice_read(packet + PACKET_HEADER_SIZE, packet[DATA_LENGTH], &size_read_local, timeout)) != RESULT::OK)
    {
      if (ret == RESULT::TIMEOUT)
      {
        return RESULT::PACKET_BODY_TIMEOUT;
      }
      return ret;
    }

    // Read last byte. It means checksum.
    if ((ret = SerialDevice_read(&buf, 1, &size_read_local, timeout)) != RESULT::OK)
    {
      if (ret == RESULT::TIMEOUT)
      {
        return RESULT::PACKET_CHECKSUM_TIMEOUT;
      }
      return ret;
    }

    // CheckSum
    uint8_t sum = 0; // PACKET_STARTING_CHARACTOR_0 + PACKET_STARTING_CHARACTOR_1;
    for (uint8_t i = 0; i < PACKET_HEADER_SIZE + packet[DATA_LENGTH]; i++)
    {
      sum += packet[i];
    }
    if (buf != sum)
    {
      return RESULT::CHECKSUM_ERROR;
    }
    *size_read = PACKET_HEADER_SIZE + packet[DATA_LENGTH];
    return RESULT::OK;
  }

} // namespace ssr::rtno