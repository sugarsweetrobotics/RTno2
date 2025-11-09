#pragma once

#if defined(__AVR__)
#elif defined(__arm__)
#include <sstream>
extern std::stringstream ss;
#else
#endif

#include "Print.h"

class Logger : public Print
{
public:
  Logger() {}
  ~Logger() {}

public:
  virtual size_t write(uint8_t);
  const char *logdata();
  const uint32_t logsize();
  void clear();

#if defined(__arm__)
  template <typename T>
  Logger &operator<<(const T value)
  {
    ss << value;
    return *this;
  }
#endif
};

const char *get_log_data();
const uint32_t get_log_data_size();
void clear_log();