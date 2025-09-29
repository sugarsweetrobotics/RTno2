/*******************************************
 * OnCommandReceiveLog.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/

#include "ecs/ExecutionContext.h"
#include "RTnoProfile.h"
#include "comm/Packet.h"
#include "comm/Command.h"
#include "comm/Transport.h"

#include "Logger.h"

using namespace ssr::rtno;

RESULT OnCommandReceiveLog(uint8_t *pPacketBuffer)
{
    const uint8_t nameLen = pPacketBuffer[PACKET_HEADER_SIZE];

    int numOutPort = RTnoProfile_getNumOutPort();
    for (int i = 0; i < numOutPort; i++)
    {
        EC_suspend();
        uint8_t data_len = get_log_data_size();
        memcpy(pPacketBuffer, get_log_data(), data_len);
        const RESULT ret = RESULT::OK;
        Transport_SendPacket(COMMAND::RECEIVE_LOG, ret, data_len, (uint8_t *)pPacketBuffer);
        clear_log();
        EC_resume();
    }
    return RESULT::OK;
}