/*******************************************
 * CommandHandler.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#pragma once

#include "Command.h"
#include <cstdint>

namespace ssr::rtno
{
    bool ReceiveCommand(uint8_t *pPacketBuffer);
    void CommandHandler_handle(uint8_t *pPacketBuffer);
}
