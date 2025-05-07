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

inline void delete_curly_brackets(std::string &s) {
    s.erase(
        std::remove(
            s.begin(),
            s.end(),
            '{'
        ),
        s.end()
    );
    s.erase(
        std::remove(
            s.begin(),
            s.end(),
            '}'
        ),
        s.end()
    );
}

inline std::string delete_curly_brackets_copy(std::string s) {
    delete_curly_brackets(s);
    return s;
}

inline unsigned int visualLen(const std::string& s) {
    unsigned int cnt = 0;
    for (size_t i = 0; i < s.size();) {
        unsigned char ch = s[i];
        if (ch >> 7 == 0) ++i;
        else if (ch >> 5 == 0x6) i += 2;
        else if (ch >> 4 == 0xE) i += 3;
        else if (ch >> 3 == 0x1E) i += 4;
        else ++i;
        ++cnt; 
    }
    return cnt;
}

inline std::string center_string(const std::string& text, unsigned int width, std::string pad = u8"\u0020") {
    int len = visualLen(text);
    if (len >= width) {
        return text;
    }

    int padding_len = width - len;
    int left_pad = padding_len / 2;
    int right_pad = padding_len - left_pad;

    std::ostringstream result;
    for (int i = 0; i < left_pad; ++i)
        result << pad;
    
    result << text;

    for (int i = 0; i < right_pad; ++i)
        result << pad;

    return result.str();
}


#endif