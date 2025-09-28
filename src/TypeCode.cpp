#include <ctype.h>

#include "TypeCode.h"

uint8_t TypeCode_isSequence(const char typeCode) {
  return isupper(typeCode);
}

uint8_t TypeCode_getElementSize(const char typeCode) {
  switch(tolower(typeCode)) {
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
  case 'd': // double is 32 bit in arduino
    return 8;
  default:
    return 4;
  }
}
