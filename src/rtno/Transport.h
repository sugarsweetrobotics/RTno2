#pragma once

#include <stdint.h>
#include "hal/SerialDevice.h"

namespace ssr::rtno
{
    RESULT Transport_init();

    RESULT Transport_SendPacket(const COMMAND command, const RESULT result, const uint8_t data_length, const uint8_t *packet_data);

    RESULT Transport_ReceivePacket(uint8_t *packet, uint8_t *size_read, const duration_t &start_packet_timeout, const duration_t &timeout);
}