/*******************************************
 * OnCommandGetState.cpp
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

RESULT OnCommandGetState(uint8_t *pPacketBuffer)
{
    const RESULT ret = RESULT::OK;
    int8_t state = EC_get_component_state();
    Transport_SendPacket(COMMAND::GET_STATE, ret, 1, (uint8_t *)&state);
    return RESULT::OK;
}