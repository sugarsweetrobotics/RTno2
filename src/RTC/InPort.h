#ifndef INPORT_HEADER_INCLUDED
#define INPORT_HEADER_INCLUDED

/*******************************************
 * InPort.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#include <stdint.h>
#include "comm/TypeCode.h"
#include "PortBase.h"
#include "NullBuffer.h"
#include <string.h>
#include <stdlib.h>

class InPortBase : public PortBase
{
private:
public:
  InPortBase(char *name, char tCode)
  {
    PortBase_init(this, name, tCode, NullBuffer_create());
  }

public:
};

template <typename T>
class InPort : public InPortBase
{
public:
  T &m_Data;

public:
  InPort(char *name, T &data) : InPortBase(name, data.typeCode), m_Data(data)
  {
  }

  ~InPort() {}

public:
  uint8_t isNew()
  {
    return pPortBuffer->hasNext(pPortBuffer);
  }

  uint8_t read()
  {
    uint8_t dataSize = pPortBuffer->getNextDataSize(pPortBuffer);
    if (TypeCode_isSequence(m_Data.typeCode))
    {
      ((SequenceBase *)&(m_Data.data))->length(dataSize / TypeCode_getElementSize(m_Data.typeCode));
      pPortBuffer->pop(pPortBuffer, (uint8_t *)((SequenceBase *)&(m_Data.data))->getData(), dataSize);
    }
    else
    {
      // This code must be okay for little endian system.
      pPortBuffer->pop(pPortBuffer, (uint8_t *)&(m_Data.data), dataSize);
    }
    return dataSize;
  }
};

#endif
