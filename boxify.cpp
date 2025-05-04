#include <iostream>
#include <string>

#include "ExtensionFinder.hpp"
#include "FileReader.hpp"
#include "CodeBlock.hpp"

#define NL '\n'
#define LINE "===========================================================\n"
#define EXTENSIONS R"(\b\w+\.c\b|\b\w+\.cpp\b|\b\w+\.cc\b|\b\w+\.cxx\b|\b\w+\.h\b|\b\w+\.hpp\b)"

int main() {
    ExtensionFinder finder(EXTENSIONS);
    
    
    for (std::string path : finder.getFileNames()) {
        std::cout << "Printing File: " << path << NL << LINE;
        FileReader fileReader(path);
        if (!fileReader.isOpen())
            return 1;

        CodeBlock codeBlock(fileReader);
        codeBlock.print();
        
        std::cout << LINE;
    }

    return 0; 
}