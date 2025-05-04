#include <iostream>
#include <string>

#include "ExtensionFinder.hpp"

#define NL '\n'
#define EXTENSIONS R"(\b\w+\.c\b|\b\w+\.cpp\b|\b\w+\.cc\b|\b\w+\.cxx\b|\b\w+\.h\b|\b\w+\.hpp\b)"

int main() {
    ExtensionFinder finder(EXTENSIONS);
    
    for (std::string path : finder.getFileNames()) 
        std::cout << path << NL;

    return 0; 
}