#ifndef LOG_H_
#define LOG_H_

#include "registry.h"

namespace zlog {

void setName(std::string& name)
{
    Registry::instance().defaultLogger()->setName(name);
}

void setLevel(Level level)
{
    Registry::instance().defaultLogger()->setLevel(level);
}

void setDefaultLogger(std::shared_ptr<Logger> new_default_logger)
{
    Registry::instance().setDefaultLogger(new_default_logger);
}

template<typename ...Args>
void debug(const std::string& str, Args&&... args)
{
    Registry::instance().defaultLogger()->debug(str, std::forward<Args>(args)...);
}

template<typename ...Args>
void info(const std::string& str, Args&&... args)
{
    Registry::instance().defaultLogger()->info(str, std::forward<Args>(args)...);
}

template<typename ...Args>
void warn(const std::string& str, Args&&... args)
{
    Registry::instance().defaultLogger()->warn(str, std::forward<Args>(args)...);
}

template<typename ...Args>
void error(const std::string& str, Args&&... args)
{
    Registry::instance().defaultLogger()->error(str, std::forward<Args>(args)...);
}

} // namespace log

#endif
