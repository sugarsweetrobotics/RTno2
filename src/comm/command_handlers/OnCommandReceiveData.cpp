/*******************************************
 * OnCommandReceiveData.cpp
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

RESULT OnCommandReceiveData(uint8_t *pPacketBuffer)
{
    const uint8_t nameLen = pPacketBuffer[PACKET_HEADER_SIZE];
    const PortBase *pOutPort = RTnoProfile_getOutPort((char *)pPacketBuffer + PACKET_HEADER_SIZE + 2, nameLen);
    if (pOutPort == NULL)
    {
        return RESULT::OUTPORT_NOT_FOUND;
    }

    EC_suspend();
    if (!pOutPort->pPortBuffer->hasNext(pOutPort->pPortBuffer))
    {
        EC_resume();
        return RESULT::OUTPORT_BUFFER_EMPTY;
    }

    const uint8_t dataLen = pOutPort->pPortBuffer->getNextDataSize(pOutPort->pPortBuffer);
    pPacketBuffer[0] = nameLen;
    pPacketBuffer[1] = dataLen;
    memcpy(pPacketBuffer + 2, pOutPort->pName, nameLen);
    pOutPort->pPortBuffer->pop(pOutPort->pPortBuffer, (uint8_t *)(pPacketBuffer + 2 + nameLen), dataLen);
    EC_resume();
    const RESULT ret = RESULT::OK;
    Transport_SendPacket(COMMAND::RECEIVE_DATA, ret, 2 + nameLen + dataLen, (uint8_t *)pPacketBuffer);
    return RESULT::OK;
}