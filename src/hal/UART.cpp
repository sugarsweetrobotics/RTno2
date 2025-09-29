/*******************************************
 * UART.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#define RTNO_SUBMODULE_DEFINE

#include <Arduino.h>
#include <HardwareSerial.h>
#include "UART.h"

static HardwareSerial *m_pSerial;

namespace ssr::rtno
{

	RESULT UART_init(unsigned char num, unsigned long baudrate)
	{
		switch (num)
		{
			// #if defined(UBRRH)
			// 	case 1:
			// 	m_pSerial = &Serial;
			// 	break;
			// #endif
			// #if defined(UBRR0H)
			// 	case 1:
			// 	m_pSerial = &Serial;
			// 	break;
			// #endif
			// #if defined(UBRR2H)
			// 		case 2:
			// 		m_pSerial = &Serial2;
			// 		break;
			// #endif
			// #if defined(UBRR3H)
			// 		case 3:
			// 		m_pSerial = &Serial3;
			// 		break;
			// #endif
		default:
			m_pSerial = &Serial;
			// return;
			break;
		}
		SerialDevice_putc = UART_putc;
		SerialDevice_getc = UART_getc;
		SerialDevice_available = UART_available;
		m_pSerial->begin(baudrate);
		return RESULT::OK;
	}

	RESULT UART_putc(const uint8_t *c)
	{
		m_pSerial->write(c, 1);
		return RESULT::OK;
	}

	RESULT UART_available()
	{
		if (m_pSerial->available())
			return RESULT::OK;
		return RESULT::NOT_AVAILABLE;
	}

	RESULT UART_getc(uint8_t *c)
	{
		*c = m_pSerial->read();
		return RESULT::OK;
	}

}