/*******************************************
 * PortBase.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef PORT_BASE_HEADER_INCLUDED
#define PORT_BASE_HEADER_INCLUDED

#include <stdint.h>
#include "BasicDataType.h"
#include "PortBuffer.h"

#define PACKET_BUFFER_SIZE 256
#define MAX_PORT 16

class PortBase
{
public:
  unsigned char portBuffer;
  void *pData;
  const char *pName;
  char typeCode;
  PortBuffer *pPortBuffer;

public:
  PortBase(const char *name, char typeCode, PortBuffer *dataBuffer) : pName(name), typeCode(typeCode), pPortBuffer(dataBuffer)
  {
  }
};

#endif
