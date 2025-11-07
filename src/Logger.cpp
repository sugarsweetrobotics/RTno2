#include "Logger.h"

Logger logger;
#if defined(__arm__)
#include <sstream>
std::stringstream ss;
#else
uint8_t log_buffer[255];
uint32_t log_buffer_index = 0;
#endif

size_t Logger::write(uint8_t v)
{
#if defined(__arm__)
    ss << v;
#else
    log_buffer[log_buffer_index++] = v;
    if (log_buffer_index >= sizeof(log_buffer))
    {
        log_buffer_index = sizeof(log_buffer) - 1;
    }
    log_buffer[log_buffer_index] = '\0';
#endif
    return 1;
}

const char *Logger::logdata()
{
#if defined(__arm__)
    return ss.str().c_str();
#else
    return (const char *)log_buffer;
#endif
    // return "This is Log";
}

const uint32_t Logger::logsize()
{
#if defined(__arm__)
    return ss.str().length();
#else
    return log_buffer_index;
#endif
    // return 11;
}

void Logger::clear()
{
#if !defined(__arm__)
    log_buffer_index = 0;
    log_buffer[0] = '\0';
    return;
#else
    ss.str("");
    ss.clear(std::stringstream::goodbit);
#endif
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