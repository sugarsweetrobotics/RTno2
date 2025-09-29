/*******************************************
 * Command.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#pragma once

enum class COMMAND : char
{
  INITIALIZE = 'I',
  ACTIVATE = 'A',
  DEACTIVATE = 'D',
  GET_STATE = 'X',

  GET_CONTEXT_TYPE = 'B',
  EXECUTE = 'E',
  RESET = 'R',

  ONERROR = 'C',
  GET_PROFILE = 'Z',
  INPORT_PROFILE = 'P',
  OUTPORT_PROFILE = 'Q',
  PLATFORM_PROFILE = 'T',

  SEND_DATA = 'S',
  RECEIVE_DATA = 'G',

  RECEIVE_LOG = 'L',

  PACKET_ERROR = 'F',
  PACKET_ERROR_CHECKSUM = 'H',
  PACKET_ERROR_TIMEOUT = 'K',
};