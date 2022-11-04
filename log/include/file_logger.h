#ifndef FILE_LOGGER_H_
#define FILE_LOGGER_H_

#include <fstream>
#include <ctime>
#include <ostream>
#include <stdexcept>

#include "logger.h"

namespace zlog {

// Logger who can write msg to a log file. Meanwhile, you can determine 
// wheither to print msg to console or not. A root dir should be given
// to save log file.
// The log file will be named like "name_-YYYY-MM-DD.txt".
class FileLogger : public Logger
{
protected:
    // Should be given whenever.
    std::string root_dir_;
    // Log file name.
    std::string dir_suffix_;
    // If true, the msg will be printed to console too.
    bool should_cout_;
public:
    FileLogger() = delete;
    FileLogger(std::string& root_dir);
    FileLogger(std::string& root_dir, bool should_cout);
    FileLogger(std::string& name, Level level, std::string& root_dir);
    FileLogger(std::string& name, Level level, std::string& root_dir, bool should_cout);
    ~FileLogger() {}

    void log(const std::string& str) override;
private:
    // Generate filename using current time.
    std::string getSuffix();
};

// ----------------------------------------------------------------------------
// implementation

FileLogger::FileLogger(std::string& root_dir) : root_dir_(root_dir) 
{
    Logger();
    should_cout_ = false;
    dir_suffix_ = getSuffix();
}

FileLogger::FileLogger(std::string& root_dir, bool should_cout) 
    : root_dir_(root_dir), should_cout_(should_cout)
{
    Logger();
    dir_suffix_ = getSuffix();
}


FileLogger::FileLogger(std::string& name, Level level, std::string& root_dir)
    : root_dir_(root_dir) 
{
    Logger(name, level);
    should_cout_ = false;
    dir_suffix_ = getSuffix();
}

FileLogger::FileLogger(std::string& name, Level level, std::string& root_dir, bool should_cout)
    : root_dir_(root_dir), should_cout_(should_cout) 
{
    Logger(name, level);
    dir_suffix_ = getSuffix();
}

void FileLogger::log(const std::string& str)
{
    std::ofstream file;
    if (should_cout_) {
        std::cout << str;
    }
    try {
        file.open(root_dir_ + dir_suffix_, std::ios::app);
        file << str;
        file.close();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }
}

std::string FileLogger::getSuffix()
{
    std::ostringstream ss;
    ss << name_ << '-';
    std::time_t now = std::time(0);
    std::tm * ltm = std::localtime(&now);
    ss << 1900 + ltm->tm_year << '-' 
       << 1 + ltm->tm_mon << '-' 
       << ltm->tm_mday;
    std::string dir_suffix = ss.str() + ".txt";

    return dir_suffix;
}

} // namespace log

#endif
