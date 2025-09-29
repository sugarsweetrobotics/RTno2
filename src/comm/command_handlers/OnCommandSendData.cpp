/*******************************************
 * OnCommandSendData.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#include "ecs/ExecutionContext.h"
#include "RTnoProfile.h"
#include "comm/Packet.h"
#include "comm/Command.h"
#include "comm/Transport.h"

using namespace ssr::rtno;

RESULT OnCommandSendData(uint8_t *pPacketBuffer)
{
    const uint8_t data_length_area_size = 2; // namelen + datalen
    const uint8_t name_len = pPacketBuffer[PACKET_HEADER_SIZE];
    const uint8_t data_len = pPacketBuffer[PACKET_HEADER_SIZE + 1];
    PortBase *pInPort = RTnoProfile_getInPort((char *)pPacketBuffer + PACKET_HEADER_SIZE + data_length_area_size, name_len);
    if (pInPort == NULL)
    {
        return RESULT::INPORT_NOT_FOUND;
    }

    PortBuffer *pBuffer = pInPort->pPortBuffer;
    EC_suspend();
    pBuffer->push(pBuffer, (const uint8_t *)&(pPacketBuffer[PACKET_HEADER_SIZE + data_length_area_size + name_len]), data_len);
    EC_resume();
    const RESULT ret = RESULT::OK;
    Transport_SendPacket(COMMAND::SEND_DATA, ret, 0, NULL);
    return RESULT::OK;
}