/*******************************************
 * OnCommandGetProfile.cpp
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
/**
 * Send Profile Data
 *
 * First, all inport profiles are sent.
 * Next, all outport profiles are sent.
 * Last, GET_PROFILE reply
 */
RESULT OnCommandGetProfile(uint8_t *pPacketBuffer)
{
    RESULT result = RESULT::OK;
    int8_t ret = RTNO_OK;
    auto platform = RTnoProfile_getPlatformInfo();
    pPacketBuffer[0] = static_cast<uint8_t>(platform.arch);
    Transport_SendPacket(COMMAND::PLATFORM_PROFILE, result, 1, (uint8_t *)pPacketBuffer);

    for (uint8_t i = 0; i < RTnoProfile_getNumInPort(); i++)
    {
        PortBase *inPort = RTnoProfile_getInPortByIndex(i);
        uint8_t nameLen = strlen(inPort->pName);
        pPacketBuffer[0] = inPort->typeCode;
        memcpy(&(pPacketBuffer[1]), inPort->pName, nameLen);
        Transport_SendPacket(COMMAND::INPORT_PROFILE, result, 1 + nameLen, (uint8_t *)pPacketBuffer);
    }

    for (uint8_t i = 0; i < RTnoProfile_getNumOutPort(); i++)
    {
        PortBase *outPort = RTnoProfile_getOutPortByIndex(i);
        uint8_t nameLen = strlen(outPort->pName);
        pPacketBuffer[0] = outPort->typeCode;
        memcpy(&(pPacketBuffer[1]), outPort->pName, nameLen);
        Transport_SendPacket(COMMAND::OUTPORT_PROFILE, result, 1 + nameLen, (uint8_t *)pPacketBuffer);
    }

    Transport_SendPacket(COMMAND::GET_PROFILE, result, 0, NULL);
    return RESULT::OK;
}
