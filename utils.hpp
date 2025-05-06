#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <cctype>
#include <locale>

inline void ltrim(std::string &s) {
    s.erase(
        s.begin(),
        std::find_if(
            s.begin(),
            s.end(),
            [](unsigned char ch){
                return !std::isspace(ch);
            }
        )
    );
} 

inline void rtrim(std::string &s) {
    s.erase(
        std::find_if(
            s.rbegin(),
            s.rend(),
            [](unsigned char ch) {
                return !std::isspace(ch);
            }
        ).base(),
        s.end()
    );
}

inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

inline std::string center_string(const std::string& text, unsigned int width, char pad = ' ') {
    int len = text.length();
    if (len >= width) {
        return text;
    }

    int padding_len = width - len;
    int left_pad = padding_len / 2;
    int right_pad = padding_len - left_pad;

    std::ostringstream result;
    result << std::setfill(pad) << std::setw(left_pad) << "";
    
    result << text;

    result << std::setfill(pad) << std::setw(right_pad) << "";

    return result.str();
}

#endif