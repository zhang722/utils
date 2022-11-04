#include "include/file_logger.h"
#include "include/log.h"

#include <fstream>

int main(){
    zlog::info("this is {.1f} formatted string", 1.f);
    zlog::setLevel(zlog::ERROR);
    zlog::info("this is {.1f} formatted string", 2.f);
    zlog::setLevel(zlog::DEBUG);
    zlog::info("this is {.1f} formatted string", 3.f);
    std::string dir = "D:\\";
    zlog::setDefaultLogger(std::make_shared<zlog::FileLogger>(dir, true));
    zlog::info("this is {.1f} formatted string", 4.f);
}