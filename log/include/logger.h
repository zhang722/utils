#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

#include "format.h"

namespace zlog {

class Logger
{
protected:
    std::string name_;
    Level level_;
public:
    Logger() : name_(""), level_(Level::INFO) {}
    Logger(std::string& name) : name_(name), level_(Level::INFO) {}
    Logger(std::string& name, Level level) : name_(name), level_(level) {}
    virtual ~Logger(){}

    virtual void log(const std::string& str) {}

    template<typename ...Args>
    void log(Level level, const std::string& str, Args&&... args);

    template<typename ...Args>
    void debug(const std::string& str, Args&&... args);

    template<typename ...Args>
    void info(const std::string& str, Args&&... args);

    template<typename ...Args>
    void warn(const std::string& str, Args&&... args);

    template<typename ...Args>
    void error(const std::string& str, Args&&... args);
};


// ----------------------------------------------------------------------------
// implementation
template<typename ...Args>
void Logger::log(Level level, const std::string& str, Args&&... args)
{
    if (level < level_) return;
    std::string msg = format(level, str, std::forward<Args>(args)...);
    log(msg);
}

template<typename ...Args>
void Logger::debug(const std::string& str, Args&&... args)
{
    log(Level::DEBUG, str, std::forward<Args>(args)...);
}

template<typename ...Args>
void Logger::info(const std::string& str, Args&&... args)
{
    log(Level::INFO, str, std::forward<Args>(args)...);
}

template<typename ...Args>
void Logger::warn(const std::string& str, Args&&... args)
{
    log(Level::WARN, str, std::forward<Args>(args)...);
}

template<typename ...Args>
void Logger::error(const std::string& str, Args&&... args)
{
    log(Level::ERROR, str, std::forward<Args>(args)...);
}

} // namespace log

#endif
