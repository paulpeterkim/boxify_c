#include "boxify.hpp"

Boxifier::Boxifier(const std::string path)
    : path(path), fileReader(path) {
    std::string line;
    while (fileReader.readLine(line)) {
        trim(line);
        if (line.size() == 0)
            continue;
        if (line.size() > 2 && line[0] == '/' && line[1] == '/') {
            continue;
        }
        // std::cout << "Adding line: " << line << NL;
        codeBlock.addLine(line);
    }
    // codeBlock.print();
}

void Boxifier::boxify() {
    size_t si = 0;
    std::vector lines = codeBlock.getLines();
    for (size_t i = 0; i < codeBlock.getLinesSize(); ++i) {
        if (codeBlock.getDepth()) {
            if (i) {
                std::cout << center_string(lines[i], codeBlock.getMaxLen() + 2) << '\n';
            } else if (!i || lines[i].front() == '}') {
                std::cout << center_string(lines[i], codeBlock.getMaxLen() + 2, '=') << '\n';
            }
        }
        while (si < codeBlock.getSubBlocksPos().size() && codeBlock.getSubBlocksPos()[si] == i) {
            codeBlock.getSubBlocks()[si++];
        } 
    }
}

int main() {
    ExtensionFinder finder(EXTENSIONS);
    
    
    // for (std::string path : finder.getFileNames()) {
    //     std::cout << "Printing File: " << path << NL << LINE;
    //     Boxifier boxifier(path);
    //     std::cout << LINE;
    // }
    // std::cout << center_string("Hello World~", 14, '=') << NL;
    Boxifier boxifier("./utils.hpp");
    boxifier.boxify();

    return 0; 
}