/*******************************************
 * OnCommandExecute.cpp
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

RESULT OnCommandExecute(uint8_t *pPacketBuffer)
{
    if (EC_get_component_state() != RTC_STATE_ACTIVE)
    {
        return RESULT::INVALID_PRESTATE;
    }
    const RESULT ret = RESULT::OK;
    int8_t retval = EC_execute();
    Transport_SendPacket(COMMAND::EXECUTE, ret, 1, (uint8_t *)&retval);
    return RESULT::OK;
}