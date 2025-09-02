#include "EtherTcp.h"


#include <Arduino.h>
#include <Ethernet.h>

namespace ssr::rtno {

static EthernetServer *m_pServer;
static EthernetClient *m_pClient;

RESULT EtherTcp_init(uint8_t* mac, uint8_t* ip, 
		   uint8_t* gateway, uint8_t* subnet,
		   uint16_t port) {
  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  m_pServer = new EthernetServer(port);

  SerialDevice_available = EtherTcp_available;
  SerialDevice_getc = EtherTcp_getc;
  SerialDevice_putc = EtherTcp_putc;

  m_pServer->begin();
  m_pClient = new EthernetClient();
  *m_pClient = m_pServer->available();
  return RESULT::OK;
}

RESULT EtherTcp_available() {
  if(*m_pClient) {
    if (m_pClient->available()) return RESULT::OK;
  } else {
    *m_pClient = m_pServer->available();
    if(*m_pClient) {
      if (m_pClient->available()) return RESULT::OK;
    }
  }
  return RESULT::NOT_AVAILABLE;
}


RESULT EtherTcp_putc(const uint8_t c) {
  m_pServer->write(c);
  return RESULT::OK;
}

RESULT EtherTcp_getc(uint8_t *c) {
  *c = m_pClient->read();
  return RESULT::OK;
}

}