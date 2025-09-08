/*******************************************
 * RTno.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/
#define RTNO_SUBMODULE_DEFINE
#include <stdint.h>
#include "Packet.h"
#include "RTno.h"
#include "Transport.h"
#include "RTnoProfile.h"


#include "Arduino.h"

using namespace ssr::rtno;

// using namespace RTno;

// global variables
// module private variables.
#define PRIVATE static


PRIVATE uint8_t m_pPacketBuffer[PACKET_BUFFER_SIZE];

/*
 * Send Profile Data
 */
PRIVATE void _SendProfile();

/**
 * Packet Handler in Error State.
 */
PRIVATE void _PacketHandlerOnError();

/**
 * Packet Handler in Inactive State.
 */
PRIVATE void _PacketHandlerOnInactive();

/**
 * Packet Handler in Active State.
 */
PRIVATE void _PacketHandlerOnActive();

void EC_setup(exec_cxt_str& exec_cxt);

ReturnValue_t EC_fault();

void Connection_setup(config_str& conf);

void Connection_setup(config_str& conf) {
  switch(conf._default.connection_type) {
#ifdef USE_ETHERNET_CONNECTION
  case ConnectionTypeEtherTcp:
    EtherTcp_init(//(uint8_t*)&conf._default.mac_address,
          conf._default.ip_address,
          conf._default.default_gateway,
          conf._default.subnet_mask,
              conf._default.port);
    break;
#endif // USE_ETHERNET_CONNECTION
#ifdef USE_UART_CONNECTION
  case ConnectionTypeSerialUSB:
    UART_init(0, conf._default.baudrate);
    break;
  case ConnectionTypeSerial1:
    UART_init(1, conf._default.baudrate);
    break;
  case ConnectionTypeSerial2:
    UART_init(2, conf._default.baudrate);
    break;
  case ConnectionTypeSerial3:
    UART_init(3, conf._default.baudrate);
    break;
#endif // USE_UART_CONNECTION
  default:
    break;
  }
}


// DataFlowComponentBase* __rtc;

void EC_setup(exec_cxt_str& exec_cxt);

int(*RTno_onInitialize)();
int(*RTno_onActivated)();
int(*RTno_onDeactivated)();
int(*RTno_onExecute)();
int(*RTno_onError)();
int(*RTno_onReset)();

/**
 * Arduino Setup Routine.
 * This function is called when arduino device is turned on.
 */
void RTno_setup(int(*on_initialize)(), int(*on_activated)(), int(*on_deactivated)(), int(*on_execute)(), int(*on_error)(), int(*on_reset)()) {

  RTnoProfile_init();
  RTno_onInitialize = on_initialize;
  RTno_onActivated = on_activated;
  RTno_onDeactivated = on_deactivated;
  RTno_onExecute = on_execute;
  RTno_onReset = on_reset;
  RTno_onError = on_error;

  exec_cxt_str* exec_cxt = (exec_cxt_str*)malloc(sizeof(exec_cxt_str));
  config_str* conf = (config_str*)malloc(sizeof(config_str));
  rtcconf(*conf, *exec_cxt);
  if(RTno_onInitialize() == RTC_OK) {
    EC_setup(*exec_cxt);
    Connection_setup(*conf);
    free(exec_cxt);
    free(conf);
    Transport_init();
    EC_start();
  }
  return;
}
//void RTno_setup(int(*on_initialize)()) {
// void RTno_setup(DataFlowComponentBase* rtc) {
//   __rtc = rtc;
//   RTnoProfile_init();
//   // This function must be called first.
//   exec_cxt_str* exec_cxt = (exec_cxt_str*)malloc(sizeof(exec_cxt_str));
//   config_str* conf = (config_str*)malloc(sizeof(config_str));
//   rtcconf(*conf, *exec_cxt);
//   if(__rtc->onInitialize() == RTC_OK) {
//     EC_setup(*exec_cxt);
//     Connection_setup(*conf);
//     free(exec_cxt);
//     free(conf);
//     Transport_init();
//     EC_start();
//   }
//   return;
// }


static int8_t m_Type = 0;
static LifeCycleState m_Condition;

void EC_init(int8_t Type) {
  m_Type = Type;
  m_Condition = RTC_STATE_INACTIVE;
}

int8_t EC_get_type() {
  return m_Type;
}

LifeCycleState EC_get_component_state() {
  return m_Condition;
}


ReturnValue_t EC_activate_component() {
  if(m_Condition != RTC_STATE_INACTIVE) {
    return RTC_PRECONDITION_NOT_MET;
  }
  
  // if(__rtc->onActivated() == RTC_OK) {
  if(RTno_onActivated() == RTC_OK) {
    m_Condition = RTC_STATE_ACTIVE;
    return RTC_OK;
  }

  m_Condition = RTC_STATE_ERROR;
  return RTC_ERROR;
}

ReturnValue_t EC_fault() {
  m_Condition = RTC_STATE_ERROR;
  return RTC_OK;
}

ReturnValue_t EC_deactivate_component() {
  if(m_Condition != RTC_STATE_ACTIVE) {
    return RTC_PRECONDITION_NOT_MET;
  }
  
  // if(__rtc->onDeactivated() == RTC_OK) {
  if(RTno_onDeactivated() == RTC_OK) {
    m_Condition = RTC_STATE_INACTIVE;
    return RTC_OK;
  } else {
    m_Condition = RTC_STATE_ERROR;
    return RTC_ERROR;
  }
}



ReturnValue_t EC_execute() {
  if(m_Condition != RTC_STATE_ACTIVE) {
    return RTC_PRECONDITION_NOT_MET;
  }
  
  // if(__rtc->onExecute() == RTC_OK) {
  if(RTno_onExecute() == RTC_OK) {
    return RTC_OK;
  } else {
    m_Condition = RTC_STATE_ERROR;
    return RTC_ERROR;
  }
}


void EC_setup(exec_cxt_str& exec_cxt) {
  switch(exec_cxt.periodic.type) {
// #ifdef USE_TIMER1_EC
//   case Timer1ExecutionContext:
//     Timer1EC_init(exec_cxt.periodic.rate);
//     break;
// #endif // USE_TIMER1_EC
//   case ProxySynchronousExecutionContext:
#if defined(__AVR__)
  case FSPTimerExecutionContext:
    TimerOneEC_init(exec_cxt.periodic.rate);
    break;
#endif
#if defined(__arm__)
  case FSPTimerExecutionContext:
    FSPTimerEC_init(exec_cxt.periodic.rate);
    break;
#endif
  default:
    ProxySyncEC_init();
    break;
  }
}


RESULT to_result(ReturnValue_t& retval) {
  switch(retval) {
    case RTC_OK: return RESULT::OK;
    case RTC_ERROR: return RESULT::ERROR;
    default: return RESULT::NONE;
  }
}

void RTno_loop() {
  RESULT ret;
  uint8_t size_read;
  uint32_t timeout = 100; // ms
  ret = Transport_ReceivePacket((uint8_t*)m_pPacketBuffer, &size_read, timeout);
  if(ret != RESULT::OK) { // Timeout Error or Checksum Error
    if (ret == RESULT::PACKET_START_TIMEOUT) {
      return;
    }
    ret = (RESULT)m_pPacketBuffer[2];
    Transport_SendPacket(COMMAND::PACKET_ERROR, ret, 1, (uint8_t*)&ret);
    return;
  } 
  else { 
    
    switch ((COMMAND)m_pPacketBuffer[INTERFACE]) {
      case COMMAND::GET_PROFILE: 
        _SendProfile();
        break;
      case COMMAND::GET_STATE: 
      {
        int8_t state = EC_get_component_state();
        Transport_SendPacket(COMMAND::GET_STATE, ret, 1, (uint8_t*)&state);
        break;
      }
      case COMMAND::GET_CONTEXT_TYPE:
      {
        int8_t type = EC_get_type();
        Transport_SendPacket(COMMAND::GET_CONTEXT_TYPE, ret, 1, (uint8_t*)&type);
        break;
      }
      case COMMAND::ACTIVATE:
      {
        if (EC_get_component_state() != RTC_STATE_INACTIVE) {
          const RESULT ret = RESULT::INVALID_PRESTATE;
          Transport_SendPacket(COMMAND::ACTIVATE, ret, 0, NULL);      
        } else {
          int8_t retval = EC_activate_component();
          Transport_SendPacket(COMMAND::ACTIVATE, ret, 1, (uint8_t*) &retval);      
        }
        break;
      }
      case COMMAND::DEACTIVATE:
      {
        if (EC_get_component_state() != RTC_STATE_ACTIVE) {
          const RESULT ret = RESULT::INVALID_PRESTATE;
          Transport_SendPacket(COMMAND::DEACTIVATE, ret, 0, NULL);      
        } else {
          int8_t retval = EC_deactivate_component();
          Transport_SendPacket(COMMAND::DEACTIVATE, ret, 1, (uint8_t*)&retval);      
        }
        break;
      }
      case COMMAND::EXECUTE:
      {
        if (EC_get_component_state() != RTC_STATE_ACTIVE) {
          const RESULT ret = RESULT::INVALID_PRESTATE;
          Transport_SendPacket(COMMAND::EXECUTE, ret, 0, NULL);      
        } else {
          int8_t retval = EC_execute();
          Transport_SendPacket(COMMAND::EXECUTE, ret, 1, (uint8_t*)&retval);      
        }
        break;
      }
      case COMMAND::SEND_DATA:
      {
        const uint8_t data_length_area_size = 2; // namelen + datalen
        const uint8_t name_len = m_pPacketBuffer[PACKET_HEADER_SIZE];
        const uint8_t data_len = m_pPacketBuffer[PACKET_HEADER_SIZE+1];
          PortBase* pInPort = RTnoProfile_getInPort((char*)m_pPacketBuffer + PACKET_HEADER_SIZE + data_length_area_size, name_len);
          if(pInPort == NULL) {
            const RESULT ret = RESULT::INPORT_NOT_FOUND; 
            Transport_SendPacket(COMMAND::SEND_DATA, ret, 0, NULL);
          } else {
            PortBuffer* pBuffer = pInPort->pPortBuffer;
            EC_suspend();
            pBuffer->push(pBuffer,(const uint8_t*)&(m_pPacketBuffer[PACKET_HEADER_SIZE + data_length_area_size + name_len]), data_len);
            EC_resume();
            const RESULT ret = RESULT::OK;
            Transport_SendPacket(COMMAND::SEND_DATA, ret, 0, NULL);
          }
        //}
        break;
      }
      case COMMAND::RECEIVE_DATA:
      {
        
        
        const uint8_t nameLen = m_pPacketBuffer[PACKET_HEADER_SIZE];

          int numOutPort = RTnoProfile_getNumOutPort();
          for(int i = 0;i < numOutPort;i++) {
            EC_suspend();
            
            PortBase* pOutPort = RTnoProfile_getOutPort((char*)m_pPacketBuffer + PACKET_HEADER_SIZE + 2, nameLen);
            if (pOutPort == NULL) {
              const RESULT ret = RESULT::OUTPORT_NOT_FOUND; 
              Transport_SendPacket(COMMAND::RECEIVE_DATA, ret, 0, NULL);
            }
            if(pOutPort->pPortBuffer->hasNext(pOutPort->pPortBuffer)) {
              char* name = pOutPort->pName;
              //uint8_t nameLen = strlen(name);
              uint8_t dataLen = pOutPort->pPortBuffer->getNextDataSize(pOutPort->pPortBuffer);

              m_pPacketBuffer[0] = nameLen;
              m_pPacketBuffer[1] = dataLen;
              memcpy(m_pPacketBuffer + 2, name, nameLen);
              pOutPort->pPortBuffer->pop(pOutPort->pPortBuffer, (uint8_t*)(m_pPacketBuffer + 2 + nameLen), dataLen);
              Transport_SendPacket(COMMAND::RECEIVE_DATA, ret, 2 + nameLen + dataLen, (uint8_t*)m_pPacketBuffer);
              return;
            } else {
              const RESULT ret = RESULT::OUTPORT_BUFFER_EMPTY; 
              Transport_SendPacket(COMMAND::RECEIVE_DATA, ret, 0, NULL);
            }
            EC_resume();
          //}
          
        }
        break;
      }
      default:
      {
        // switch(EC_get_component_state()) {
        // // case RTC_STATE_ERROR:
        // //   _PacketHandlerOnError();
        // //   break;
        // case RTC_STATE_INACTIVE:
        //   //_PacketHandlerOnInactive();
        //   break;
        // // case RTC_STATE_ACTIVE:
        // //   _PacketHandlerOnActive();
        // //   break;
        // // case RTC_STATE_NONE:
        // //   ret = RTNO_NONE;
        // //   Transport_SendPacket(m_pPacketBuffer[INTERFACE], 1, (int8_t*)&ret);
        // //   break;
        // default: // if m_Condition is unknown..
        //   break;
        // }
      }
    }
      
  }
}

/**
 * Arduino Loop routine.
 * This function is repeadedly called when arduino is turned on.
 */
#if 0
void RTno_loop_() {
  int8_t ret;
  uint32_t timeout = 20*1000;
  ret = Transport_ReceivePacket((uint8_t*)m_pPacketBuffer, timeout);
  if(ret < 0) { // Timeout Error or Checksum Error
    if(ret == -CHECKSUM_ERROR) {
		  Transport_SendPacket(PACKET_ERROR_CHECKSUM, 1, (int8_t*)&ret);
    } else if(ret == -TIMEOUT) {
      Transport_SendPacket(PACKET_ERROR_TIMEOUT, 1, (int8_t*)&ret);
    }else {
    	Transport_SendPacket(PACKET_ERROR, 1, (int8_t*)&ret);
    }
  } else if (ret == 0) {

  } else if (ret > 0) { // Packet is successfully received
    if (m_pPacketBuffer[INTERFACE] == GET_PROFILE) {
      _SendProfile();
    } else if (m_pPacketBuffer[INTERFACE] == GET_STATUS) {
      int8_t state = EC_get_component_state();
      Transport_SendPacket(GET_STATUS, 1, &state);
    } else if (m_pPacketBuffer[INTERFACE] == GET_CONTEXT) {
      int8_t type = EC_get_type();
      Transport_SendPacket(GET_CONTEXT, 1, &type);
    } else if (m_pPacketBuffer[INTERFACE] == ACTIVATE) {
      

    } else {
      switch(EC_get_component_state()) {
      case RTC_STATE_ERROR:
        _PacketHandlerOnError();
        break;
      case RTC_STATE_INACTIVE:
        _PacketHandlerOnInactive();
        break;
      case RTC_STATE_ACTIVE:
        _PacketHandlerOnActive();
        break;
      case RTC_STATE_NONE:
        ret = RTNO_NONE;
        Transport_SendPacket(m_pPacketBuffer[INTERFACE], 1, (int8_t*)&ret);
    break;
      default: // if m_Condition is unknown...
    
    break;
      }
    }
  }

  
  // int numOutPort = RTnoProfile_getNumOutPort();
  // for(int i = 0;i < numOutPort;i++) {
  //   EC_suspend();
  //   PortBase* pOutPort = RTnoProfile_getOutPortByIndex(i);
  //   if(pOutPort->pPortBuffer->hasNext(pOutPort->pPortBuffer)) {
  //     char* name = pOutPort->pName;
  //     unsigned char nameLen = strlen(name);
  //     unsigned char dataLen = pOutPort->pPortBuffer->getNextDataSize(pOutPort->pPortBuffer);

  //     m_pPacketBuffer[0] = nameLen;
  //     m_pPacketBuffer[1] = dataLen;
  //     memcpy(m_pPacketBuffer + 2, name, nameLen);
  //     pOutPort->pPortBuffer->pop(pOutPort->pPortBuffer, m_pPacketBuffer + 2 + nameLen, dataLen);
  //     Transport_SendPacket(RECEIVE_DATA, 2 + nameLen + dataLen, m_pPacketBuffer);
  //   }
  //   EC_resume();
  // }
  
}

#endif 


/**
 * Private Function Definitions
 *
 */


/**
 * Send Profile Data
 * 
 * First, all inport profiles are sent.
 * Next, all outport profiles are sent.
 * Last, GET_PROFILE reply
 */
PRIVATE void _SendProfile() {
  RESULT result = RESULT::OK;
  int8_t ret = RTNO_OK;
  for(uint8_t i = 0;i < RTnoProfile_getNumInPort();i++) {
    PortBase* inPort = RTnoProfile_getInPortByIndex(i);
    uint8_t nameLen = strlen(inPort->pName);
    m_pPacketBuffer[0] = inPort->typeCode;
    memcpy(&(m_pPacketBuffer[1]), inPort->pName, nameLen);
    Transport_SendPacket(COMMAND::INPORT_PROFILE, result, 1+nameLen, (uint8_t*)m_pPacketBuffer);
  }

  for(uint8_t i = 0;i < RTnoProfile_getNumOutPort();i++) {
    PortBase* outPort = RTnoProfile_getOutPortByIndex(i);
    uint8_t nameLen = strlen(outPort->pName);
    m_pPacketBuffer[0] = outPort->typeCode;
    memcpy(&(m_pPacketBuffer[1]), outPort->pName, nameLen);
    Transport_SendPacket(COMMAND::OUTPORT_PROFILE, result, 1+nameLen, (uint8_t*)m_pPacketBuffer);
  }

  Transport_SendPacket(COMMAND::GET_PROFILE, result, 0, NULL);
}



// /**
//  * Packet Handler in Error State
//  */
// PRIVATE void _PacketHandlerOnError() {
//   char intface;
//   int8_t ret = RTNO_OK;

//   int8_t retval = EC_error();
//   if(retval < 0) ret = RTNO_ERROR;
//   Transport_SendPacket(intface, 1, (int8_t*)&ret);
// }


/** 
 * Packet Handler in Inactive State
 */
PRIVATE void _PacketHandlerOnInactive() {

  // int8_t ret = RTNO_OK;
  // int8_t retval = EC_activate_component();
  // if(retval < 0) ret = RTNO_ERROR;
  // Transport_SendPacket(ACTIVATE, 1, &ret);
}

#if 0
/**
 * Packet Handler in Active State.
 */
PRIVATE void _PacketHandlerOnActive() {
  int8_t ret = RTNO_OK;
  //char intface;
  int8_t retval;
  switch(m_pPacketBuffer[INTERFACE]) {
  case DEACTIVATE:
    retval = EC_deactivate_component();
    if(retval < 0) ret = RTNO_ERROR;
    Transport_SendPacket(DEACTIVATE, 1, &ret);
    break;
  case EXECUTE:
    retval = EC_execute();
    if(retval < 0) ret = RTNO_ERROR;
    Transport_SendPacket(EXECUTE, 1, &ret);
    break;
  case SEND_DATA: {
      PortBase* pInPort = RTnoProfile_getInPort((char*)m_pPacketBuffer + 2 + 2, m_pPacketBuffer[2]);
      if(pInPort == NULL) {
        ret = RTNO_ERROR;   
        Transport_SendPacket(SEND_DATA, 1, &ret);
      } else {
        PortBuffer* pBuffer = pInPort->pPortBuffer;
        EC_suspend();
        pBuffer->push(pBuffer,&(m_pPacketBuffer[2 + 2 + m_pPacketBuffer[2]]), m_pPacketBuffer[2+1]);
        EC_resume();
        Transport_SendPacket(SEND_DATA, 1, &ret);
      }
    }
    break;
  default:
    break;
  }
}
#endif 
