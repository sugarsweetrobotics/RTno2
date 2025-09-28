#pragma once

#include <sstream>
#include "Print.h"

extern std::stringstream ss;

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

  template <typename T>
  Logger &operator<<(const T value)
  {
    ss << value;
    return *this;
  }
};

const char *get_log_data();
const uint32_t get_log_data_size();
void clear_log();