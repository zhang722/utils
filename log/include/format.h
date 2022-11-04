#ifndef FORMAT_H_
#define FORMAT_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

namespace zlog {

enum Level : int {
    DEBUG = 0,
    INFO,
    WARN,
    ERROR
};

struct Info {
    size_t start;
    size_t end;
    int sign;
    int precision;
};

int getPrecision(const std::string& subfmt) {
    size_t len = subfmt.length();
    size_t index = 0;
    if (len < 2 || subfmt[index] != '.') 
        return -1;

    ++index;
    if (subfmt[index] > '9' || subfmt[index] < '0') 
        return -1;
    return static_cast<int>(subfmt[index] - '0');
};

Info getInfo(const std::string& fmt)
{
    Info info{0, 0 , 0, -1};

    size_t lp = fmt.find('{', 0);
    if (lp == std::string::npos) return info;
    size_t rp = fmt.find('}', lp);
    if (rp == std::string::npos) return info;

    info.start = lp;
    info.end = rp;

    if (rp - lp < 2) return info;

    switch (fmt[lp + 1]) {
        case '+':
        case '-':
            info.sign = 1;
            info.precision = getPrecision(fmt.substr(lp + 2, rp - lp - 2));
            break;
        default:
            info.sign = 0;
            info.precision = getPrecision(fmt.substr(lp + 1, rp - lp - 1));
    }

    return info;
}

template<typename Stream, typename T, typename ...Args>
void format_ipl(Stream& stream, const std::string& str, T&& value, Args&&... args)
{
    Info info = getInfo(str);
    stream << str.substr(0, info.start);
    if (info.sign == 1) {
        if (info.precision != -1) {
            stream << std::showpos << std::fixed << std::setprecision(info.precision) << value;
        } else {
            stream << std::showpos << value;
        }
    }
    else {
        if (info.precision != -1) {
            stream << std::fixed << std::setprecision(info.precision) << value;
        } else {
            stream << value;
        }
    }
    if constexpr (sizeof...(Args) > 0) {
        format_ipl(stream, str.substr(info.end + 1), std::forward<Args>(args)...);
    }
    else {
        stream << str.substr(info.end + 1);
    }
}


template<typename ...Args>
std::string format(Level level, const std::string& str, Args&&... args) {
    std::ostringstream ss;
    // add time
    std::time_t now = std::time(0);
    std::tm * ltm = std::localtime(&now);
    ss << '[';
    ss << 1900 + ltm->tm_year << '.' 
       << 1 + ltm->tm_mon << '.' 
       << ltm->tm_mday;
    ss << '-';
    ss << 1 + ltm->tm_hour << ":";
    ss << 1 + ltm->tm_min << ":";
    ss << 1 + ltm->tm_sec << ']';

    std::vector<std::string> levels = {
        "[DEBUG]",
        "[INFO]",
        "[WARN]",
        "[ERROR]"
    };
    ss << levels[static_cast<size_t>(level)];

    format_ipl(ss, str, std::forward<Args>(args)...);
    ss << '\n';

    return ss.str();
}

} // namespace log

#endif
