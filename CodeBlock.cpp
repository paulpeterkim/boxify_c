#include "CodeBlock.hpp"

#include <string>
#include <iostream>

using std::string;

CodeBlock::CodeBlock() {}
CodeBlock::CodeBlock(int prev_depth) : depth(prev_depth + 1) {}

// Needs to pass in trimmed string line.
unsigned int CodeBlock::addLine(string line) {
    bool isSubBlockStart = line.back() == '{';
    bool isSubBlockEnd = line.front() == '}';

    unsigned int len = line.length();

    

    if (!lines.size()) {
        lines.push_back(line);
        // std::cout << "Adding to depth " << depth << " line: " << line << std::endl;
        if (len > max_len) {
            max_len = len;
        }
        return len;
    }

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
            if (!subBlocks.back().delegateToSubBlocks)
                delegateToSubBlocks = false;
            len = subBlocks.back().addLine(line) + 2;
        } else {
            // ~
            len = subBlocks.back().addLine(line) + 2;
        }
    } else {
        if (isSubBlockStart) {
            // ~ {
            subBlocksPosArr.push_back(lines.size() - 1);
            subBlocks.push_back(CodeBlock(depth));
            len = subBlocks.back().addLine(line) + 2;
            delegateToSubBlocks = true;
        } else {
            lines.push_back(line);
            // std::cout << "Adding to depth " << depth << " line: " << line << std::endl;
        }
    }

    if (len > max_len) {
        max_len = len;
    }

    return len;
}

vector<string>& CodeBlock::getLines() {
    return lines;
}

unsigned int CodeBlock::getLinesSize() {
    return lines.size();
}

vector<CodeBlock>& CodeBlock::getSubBlocks() {
    return subBlocks;
}

vector<unsigned int>& CodeBlock::getSubBlocksPos() {
    return subBlocksPosArr;
}

unsigned int CodeBlock::getDepth() {
    return depth;
}

unsigned int CodeBlock::getMaxLen() {
    return max_len;
}

void CodeBlock::print() {
    size_t si = 0;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (i && lines[i].front() != '}')
            for (int j = 0; j < depth; ++j)
                std::cout << '\t';
        else if (depth > 0 || lines[i].front() == '}') 
            for (int j = 0; j < depth - 1; ++j)
                std::cout << '\t';
        // std::cout << depth << "-" << i << ": " << lines[i] << '\n';
        std::cout << lines[i] << '\n';
        while (si < subBlocksPosArr.size() && subBlocksPosArr[si] == i) {
            subBlocks[si++].print();
            // std::cout << subBlocks[si - 1].max_len << std::endl;
        } 
    }
}