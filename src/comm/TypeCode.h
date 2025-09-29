/*******************************************
 * TypeCode.h
 * @author Yuki Suga
 * @copyright Yuki Suga (SUGAR SWEET ROBOTICS) Oct, 1st, 2025
 * @license LGPLv3
 *****************************************/
#pragma once

#include <stdint.h>
#include <ctype.h>

enum class TYPECODE : char
{
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

// #define TYPECODE_TIMED_BOOLEAN 'b'
// #define TYPECODE_TIMED_CHAR 'c'
// #define TYPECODE_TIMED_OCTET 'o'

// #define TYPECODE_TIMED_LONG 'l'
// #define TYPECODE_TIMED_FLOAT 'f'
// #define TYPECODE_TIMED_DOUBLE 'd'

// #define TYPECODE_TIMED_BOOLEAN_SEQ 'B'
// #define TYPECODE_TIMED_CHAR_SEQ 'C'
// #define TYPECODE_TIMED_OCTET_SEQ 'O'

// #define TYPECODE_TIMED_LONG_SEQ 'L'
// #define TYPECODE_TIMED_FLOAT_SEQ 'F'
// #define TYPECODE_TIMED_DOUBLE_SEQ 'D'

inline uint8_t TypeCode_isSequence(const char typeCode)
{
    return isupper(typeCode);
}

inline uint8_t TypeCode_getElementSize(const char typeCode)
{
    switch (tolower(typeCode))
    {
    case 'b':
    case 'c':
    case 'o':
        return 1;
    case 's':
        return 2;
    case 'l':
        return 4;
    case 'f':
        return 4;
    case 'd':
#if defined(__AVR__)
        return 4; // In AVR arduino, double is float!
#else
        return 8;
#endif
    default:
        return 4;
    }
}
