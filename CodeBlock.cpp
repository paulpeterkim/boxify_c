#include "CodeBlock.hpp"

#include <string>
#include <iostream>

using std::string;

CodeBlock::CodeBlock(FileReader& fp) : fp(fp) {
    string line;
    while (fp.readLine(line))
        // Start of new subcode block.
        if (line.back() == '{') {
            subBlocks.push_back(CodeBlock(fp, line));
        }
        lines.push_back(line);
}

CodeBlock::CodeBlock(FileReader& fp, string prev_line) : fp(fp) {
    string line;
    
    lines.push_back(prev_line);
    while (fp.readLine(line))
        // Start of new subcode block.
        if (line.back() == '{') {
            subBlocks.push_back(CodeBlock(fp, line));
        }
        lines.push_back(line);
}

void CodeBlock::print() {
    for (string line: lines)
        std::cout << line << std::endl;
}