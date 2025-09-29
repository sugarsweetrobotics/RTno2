/*******************************************
 * CommandHandler.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#include "CommandHandler.h"
#include "comm/Transport.h"
#include "Packet.h"

#include <cstdio>

bool ssr::rtno::ReceiveCommand(uint8_t *pPacketBuffer)
{
    RESULT ret;
    uint8_t size_read;
    uint32_t timeout = 100; // ms
    ret = Transport_ReceivePacket((uint8_t *)pPacketBuffer, &size_read, timeout);
    if (ret != RESULT::OK)
    { // Timeout Error or Checksum Error
        if (ret == RESULT::PACKET_START_TIMEOUT)
        {
            return false;
        }
        ret = (RESULT)pPacketBuffer[2];
        Transport_SendPacket(COMMAND::PACKET_ERROR, ret, 1, (uint8_t *)&ret);
        return false;
    }
    return true;
}

static RESULT CommandHandler_handle_inner(COMMAND cmd, uint8_t *pPacketBuffer);

void ssr::rtno::CommandHandler_handle(uint8_t *pPacketBuffer)
{
    COMMAND cmd = (COMMAND)pPacketBuffer[INTERFACE];
    RESULT result = CommandHandler_handle_inner(cmd, pPacketBuffer);
    if (result != RESULT::OK)
    {
        Transport_SendPacket(cmd, result, 0, NULL);
    }
}

/*
 * Send Profile Data
 */
RESULT OnCommandGetProfile(uint8_t *pPacketBuffer);

RESULT OnCommandGetState(uint8_t *pPacketBuffer);

RESULT OnCommandGetContextType(uint8_t *pPacketBuffer);

RESULT OnCommandActivate(uint8_t *pPacketBuffer);

RESULT OnCommandDeactivate(uint8_t *pPacketBuffer);

RESULT OnCommandExecute(uint8_t *pPacketBuffer);

RESULT OnCommandSendData(uint8_t *pPacketBuffer);

RESULT OnCommandReceiveData(uint8_t *pPacketBuffer);

RESULT OnCommandReceiveLog(uint8_t *pPacketBuffer);

RESULT CommandHandler_handle_inner(COMMAND cmd, uint8_t *pPacketBuffer)
{
    switch (cmd)
    {
    case COMMAND::GET_PROFILE:
        return OnCommandGetProfile(pPacketBuffer);
    case COMMAND::GET_STATE:
        return OnCommandGetState(pPacketBuffer);
    case COMMAND::GET_CONTEXT_TYPE:
        return OnCommandGetContextType(pPacketBuffer);
    case COMMAND::ACTIVATE:
        return OnCommandActivate(pPacketBuffer);
    case COMMAND::DEACTIVATE:
        return OnCommandDeactivate(pPacketBuffer);
    case COMMAND::EXECUTE:
        return OnCommandExecute(pPacketBuffer);
    case COMMAND::SEND_DATA:
        return OnCommandSendData(pPacketBuffer);
    case COMMAND::RECEIVE_DATA:
        return OnCommandReceiveData(pPacketBuffer);
    case COMMAND::RECEIVE_LOG:
        return OnCommandReceiveLog(pPacketBuffer);
    default:
        return RESULT::UNKNOWN_COMMAND;
    }
}