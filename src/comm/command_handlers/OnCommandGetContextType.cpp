/*******************************************
 * OnCommandGetContextType.cpp
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

RESULT OnCommandGetContextType(uint8_t *pPacketBuffer)
{
    const RESULT ret = RESULT::OK;
    int8_t type = EC_get_type();
    Transport_SendPacket(COMMAND::GET_CONTEXT_TYPE, ret, 1, (uint8_t *)&type);
    return RESULT::OK;
}
