#ifndef TYPECODE_HEADER_INCLUDED
#define TYPECODE_HEADER_INCLUDED

#include <stdint.h>
// uint8_t TypeCode_isSequence(const char typeCode);

// uint8_t TypeCode_getElementSize(const char typeCode);

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

constexpr bool is_ascii_upper(char c)
{
    return (c >= 'A' && c <= 'Z');
}

constexpr uint8_t TypeCode_isSequence(const char type_code)
{
    return is_ascii_upper(type_code);
}

constexpr char ascii_tolower(const char c)
{
    return (c >= 'A' && c <= 'Z') ? static_cast<char>(c + ('a' - 'A')) : c;
}

constexpr uint8_t TypeCode_getElementSizeInner(const char type_code)
{

#if defined(__AVR__)
    return (type_code == 'b' || type_code == 'c' || type_code == 'o') ? 1 : (type_code == 's')                   ? 2
                                                                        : (type_code == 'l' || type_code == 'f') ? 4
                                                                        : (type_code == 'd')                     ? 4
                                                                                                                 : 4;
#elif defined(__arm__)
    return (type_code == 'b' || type_code == 'c' || type_code == 'o') ? 1 : (type_code == 's')                   ? 2
                                                                        : (type_code == 'l' || type_code == 'f') ? 4
                                                                        : (type_code == 'd')                     ? 8
                                                                                                                 : 4;
#else
    return (type_code == 'b' || type_code == 'c' || type_code == 'o') ? 1 : (type_code == 's')                   ? 2
                                                                        : (type_code == 'l' || type_code == 'f') ? 4
                                                                        : (type_code == 'd')                     ? 8
                                                                                                                 : 4;
#endif
}

constexpr uint8_t TypeCode_getElementSize(const char type_code)
{
    return TypeCode_getElementSizeInner(ascii_tolower(type_code));
}

#endif // #ifndef TYPECODE_HEADER_INCLUDED
