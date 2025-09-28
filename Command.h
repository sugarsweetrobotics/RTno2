#pragma once



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

  RECEIVE_LOG = 'L',
  
  PACKET_ERROR = 'F',
  PACKET_ERROR_CHECKSUM = 'H',
  PACKET_ERROR_TIMEOUT = 'K',
};