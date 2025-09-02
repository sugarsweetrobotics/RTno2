/*******************************************
 * Packet.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef PACKET_HEADER_INCLUDED
#define PACKET_HEADER_INCLUDED

#include "Result.h"

// Return Values
// #define TIMEOUT 1
// #define DATA_TIMEOUT 2
// #define CHECKSUM_ERROR 3

#define INVALID_PACKET_INTERFACE 65
#define INVALID_PACKET_DATASIZE  66

// Packet Settings
#define STARTING_HEADER_SIZE 2
#define PACKET_HEADER_SIZE 2
#define INTERFACE 0
#define DATA_LENGTH 1
//#define DATA_START_ADDR 2+4

#define PACKET_STARTING_CHARACTOR_0 0x0a
#define PACKET_STARTING_CHARACTOR_1 0x0a

enum {
  RTC_STATE_CREATED='C',
  RTC_STATE_INACTIVE='I',
  RTC_STATE_ACTIVE='A',
  RTC_STATE_ERROR='E',
  RTC_STATE_NONE='N',
};


// Protocol

enum class COMMAND : char {
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

  SEND_DATA = 'S',
  RECEIVE_DATA = 'G',
  
  PACKET_ERROR = 'F',
  PACKET_ERROR_CHECKSUM = 'H',
  PACKET_ERROR_TIMEOUT = 'K',
  // RECEIVE_DATA = 'V',

  // INPORT_ISNEW = 'N',
  // INPORT_READ  = 'J',
};

// #define INITIALIZE 'I'
// #define ACTIVATE 'A'
// #define DEACTIVATE 'D'
// #define EXECUTE 'E'
// #define ONERROR 'C'
// #define RESET 'R'
// #define GET_STATUS 'X'
// #define GET_DATA 'G'
// #define SEND_DATA 'S'
// #define GET_PROFILE 'Z'
// #define GET_CONTEXT 'B'
// #define PACKET_ERROR 'F'
// #define PACKET_ERROR_CHECKSUM 'H'
// #define PACKET_ERROR_TIMEOUT 'K'
// #define RECEIVE_DATA 'V'

// #define ADD_INPORT 'P'
// #define ADD_OUTPORT 'Q'

// #define INPORT_ISNEW 'N'
// #define INPORT_READ  'J'



#define RTNO_OK '@'
#define RTNO_ERROR 'x'
#define RTNO_NONE '!'

#define OUTPORT_WRITE 'W'

// Communication Settings
#define PACKET_WAITING_TIME 100 // ms
#define PACKET_WAITING_DELAY 100 //us
#define PACKET_WAITING_COUNT (PACKET_WAITING_TIME*1000/PACKET_WAITING_DELAY)


enum class TYPECODE : char {
  TIMED_BOOLEAN = 'b',
  TIMED_BOOLEAN_SEQ = 'B',
  TIMED_CHAR = 'c',
  TIMED_CHAR_SEQ = 'C',
  TIMED_OCTET = 'o',
  TIMED_OCTET_SEQ = 'O',
  TIMED_LONG = 'l',
  TIMED_LONG_SEQ = 'L',
  TIMED_FLOAT = 'f',
  TIMED_FLOAT_SEQ = 'F',
  TIMED_DOUBLE = 'd',
  TIMED_DOUBLE_SEQ = 'D',
};

#define TYPECODE_TIMED_BOOLEAN 'b'
#define TYPECODE_TIMED_CHAR 'c'
#define TYPECODE_TIMED_OCTET 'o'


#define TYPECODE_TIMED_LONG 'l'
#define TYPECODE_TIMED_FLOAT 'f'
#define TYPECODE_TIMED_DOUBLE 'd'

#define TYPECODE_TIMED_BOOLEAN_SEQ 'B'
#define TYPECODE_TIMED_CHAR_SEQ 'C'
#define TYPECODE_TIMED_OCTET_SEQ 'O'


#define TYPECODE_TIMED_LONG_SEQ 'L'
#define TYPECODE_TIMED_FLOAT_SEQ 'F'
#define TYPECODE_TIMED_DOUBLE_SEQ 'D'

#endif
