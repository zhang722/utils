#ifndef REGISTRY_H_
#define REGISTRY_H_

#include <memory>

#include "stdout_logger.h"
#include "file_logger.h"

namespace zlog {

class Registry
{
public:
    // prohibit copy constructor and copy assignment 
    Registry(const Registry&) = delete;
    Registry& operator=(const Registry&) = delete;

    static Registry& instance();
    std::shared_ptr<Logger> defaultLogger();
    void setDefaultLogger(std::shared_ptr<Logger> new_default_logger);
private:
    // make constructor private
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
