#ifndef STDOUT_LOGGER_H_
#define STDOUT_LOGGER_H_

#include "logger.h"

namespace zlog {
    
class StdoutLogger : public Logger
{
public:
    StdoutLogger() : Logger() {}
    StdoutLogger(std::string& name) : Logger(name) {}
    StdoutLogger(std::string& name, Level level) : Logger(name, level) {}
    ~StdoutLogger() {}

    void log(const std::string& str) override;
};

// ----------------------------------------------------------------------------
// implementation

void StdoutLogger::log(const std::string& str)
{
    std::cout << str;
}

} // namespace zlog

#endif
