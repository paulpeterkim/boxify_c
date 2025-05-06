#include "CodeBlock.hpp"

#include <string>
#include <iostream>

using std::string;


CodeBlock::CodeBlock(int prev_depth) : depth(prev_depth + 1) {}

// Needs to pass in trimmed string line.
unsigned int CodeBlock::addLine(string line) {
    bool isSubBlockStart = line.back() == '{';
    bool isSubBlockEnd = line.front() == '}';

    unsigned int len = line.length();

    if (delegateToSubBlocks) {
        if (isSubBlockStart && isSubBlockEnd) {
            // } ~~ {
            subBlocksPosArr.push_back(lines.size() - 1);
            subBlocks.push_back(CodeBlock(depth));
            len = subBlocks.back().addLine(line) + 2;
        } else if (isSubBlockStart && !isSubBlockEnd) {
            // ~ {
            len = subBlocks.back().addLine(line) + 2;
        } else if (!isSubBlockStart && isSubBlockEnd) {
            // }
            len = subBlocks.back().addLine(line) + 2;
            delegateToSubBlocks = false;
        } else {
            // ~
            len = subBlocks.back().addLine(line) + 2;
        }
    } else {
        if (isSubBlockStart) {
            // ~ {
            // It is start of sub-block.
            subBlocksPosArr.push_back(lines.size() - 1);
            subBlocks.push_back(CodeBlock(depth));
            len = subBlocks.back().addLine(line) + 2;
            delegateToSubBlocks = true;
        } else {
            lines.push_back(line);
        }
    }
    if (len > max_len) {
        max_len = len;
    }

    return len;
}

void CodeBlock::print() {
    size_t i = 0;
    for (size_t si = 0; si < subBlocksPosArr.size(); ++si) {
        for (; i < lines.size(); ++i) {
            for (int j = 0; j < depth; ++j)
                std::cout << '\t';
            std::cout << lines[i] << '\n';
            if (subBlocksPosArr[si] == i)
                break;
        }
        subBlocks[si].print();
    }
}