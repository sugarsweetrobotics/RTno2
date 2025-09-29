/*******************************************
 * Packet.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/

#pragma once

#include "Result.h"

// Return Values
// #define TIMEOUT 1
// #define DATA_TIMEOUT 2
// #define CHECKSUM_ERROR 3

#define INVALID_PACKET_INTERFACE 65
#define INVALID_PACKET_DATASIZE 66

// Packet Settings
#define STARTING_HEADER_SIZE 2
#define PACKET_HEADER_SIZE 3
#define INTERFACE 0
#define PACKET_INDEX_RESULT 1
#define DATA_LENGTH 2
// #define DATA_START_ADDR 2+4

#define PACKET_STARTING_CHARACTOR_0 0x0a
#define PACKET_STARTING_CHARACTOR_1 0x0a

enum
{
  RTC_STATE_CREATED = 'C',
  RTC_STATE_INACTIVE = 'I',
  RTC_STATE_ACTIVE = 'A',
  RTC_STATE_ERROR = 'E',
  RTC_STATE_NONE = 'N',
};

// Protocol
#include "Command.h"

#define RTNO_OK '@'
#define RTNO_ERROR 'x'
#define RTNO_NONE '!'

#define OUTPORT_WRITE 'W'

// Communication Settings
#define PACKET_WAITING_TIME 100  // ms
#define PACKET_WAITING_DELAY 100 // us
#define PACKET_WAITING_COUNT (PACKET_WAITING_TIME * 1000 / PACKET_WAITING_DELAY)

#include "TypeCode.h"
