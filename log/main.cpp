#include "include/file_logger.h"
#include "include/stdout_logger.h"

#include <fstream>


int main(){
    // std::ofstream file;
    // file.open("D:\\a.txt");
    // file << "aaa";
    // file.close();
    std::string dir = "D:\\";
    zlog::FileLogger log(dir, false);
    log.warn("this is {+.2f} format {afdafd} aaa{}", 21.34, "ser");
    zlog::StdoutLogger loggg;
    loggg.error("this is {+.2f} format {afdafd} aaa{}", 21.34, "ser");
}