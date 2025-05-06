#ifndef BOXIFY_HPP
#define BIXIFY_HPP

#include <iostream>
#include <string>

#include "ExtensionFinder.hpp"
#include "FileReader.hpp"
#include "CodeBlock.hpp"
#include "utils.hpp"

#define NL '\n'
#define LINE "===========================================================\n"
#define EXTENSIONS R"(\b\w+\.c\b|\b\w+\.cpp\b|\b\w+\.cc\b|\b\w+\.cxx\b|\b\w+\.h\b|\b\w+\.hpp\b)"

class Boxifier {
private:
    std::string path;
    FileReader fileReader;
    CodeBlock codeBlock;

public:
    Boxifier(const std::string path);
    void boxify();
};
    
#endif