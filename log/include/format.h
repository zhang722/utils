#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

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
void format(Stream& stream, const std::string& str, T&& value, Args&&... args)
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
        format(stream, str.substr(info.end + 1), std::forward<Args>(args)...);
    }
    else {
        stream << str.substr(info.end + 1);
    }
}

