#ifndef REGISTRY_H_
#define REGISTRY_H_

#include <memory>

#include "stdout_logger.h"
#include "file_logger.h"

namespace zlog {

// This class if for maintaining a global default logger. The design pattern 
// called Singleton Pattern is used.
class Registry
{
public:
    // Prohibit copy constructor and copy assignment.
    Registry(const Registry&) = delete;
    Registry& operator=(const Registry&) = delete;

    static Registry& instance();
    std::shared_ptr<Logger> defaultLogger();
    void setDefaultLogger(std::shared_ptr<Logger> new_default_logger);
private:
    // Make constructor private.
    Registry();
    ~Registry();

    std::shared_ptr<Logger> default_logger_;
};

// ----------------------------------------------------------------------------
// implementation

Registry::Registry()
{
    std::string default_logger_name = "";
    default_logger_ = std::make_shared<StdoutLogger>(default_logger_name);
}

Registry::~Registry()
{
}

Registry& Registry::instance() 
{
    static Registry s_instance;
    return s_instance;
}
    
std::shared_ptr<Logger> Registry::defaultLogger()
{
    return default_logger_;
}

void Registry::setDefaultLogger(std::shared_ptr<Logger> new_default_logger)
{
    default_logger_ = std::move(new_default_logger);
}

} // namespace zlog

#endif
