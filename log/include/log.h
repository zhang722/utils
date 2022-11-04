#include "format.h"

namespace zlog {


enum Level : int {
    DEBUG = 0,
    INFO,
    WARN,
    ERROR
};

Level glevel = Level::INFO;

template<typename ...Args>
void log(const std::string& str, Args&&... args)
{
    format(std::cout, str, std::forward<Args>(args)...);
}

template<typename ...Args>
void log(Level level, const std::string& str, Args&&... args)
{
    if (level < glevel) return;
    log(str, std::forward<Args>(args)...);
}

template<typename ...Args>
void debug(const std::string& str, Args&&... args)
{
    log(Level::DEBUG, str, std::forward<Args>(args)...);
}

template<typename ...Args>
void info(const std::string& str, Args&&... args)
{
    log(Level::INFO, str, std::forward<Args>(args)...);
}

template<typename ...Args>
void warn(const std::string& str, Args&&... args)
{
    log(Level::WARN, str, std::forward<Args>(args)...);
}

template<typename ...Args>
void error(const std::string& str, Args&&... args)
{
    log(Level::ERROR, str, std::forward<Args>(args)...);
}

} // namespace log