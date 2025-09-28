#include "Logger.h"
#include <sstream>

Logger logger;
std::stringstream ss;

size_t Logger::write(uint8_t v)
{
    ss << v;
    return 1;
}

const char *Logger::logdata()
{
    return ss.str().c_str();
    // return "This is Log";
}

const uint32_t Logger::logsize()
{
    return ss.str().length();
    // return 11;
}

void Logger::clear()
{
    ss.str("");
    ss.clear(std::stringstream::goodbit);
}

const char *get_log_data()
{
    return logger.logdata();
}

const uint32_t get_log_data_size()
{
    return logger.logsize();
}

void clear_log()
{
    logger.clear();
}