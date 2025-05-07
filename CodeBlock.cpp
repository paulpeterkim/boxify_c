#include "CodeBlock.hpp"

#include <string>
#include <iostream>

using std::string;

CodeBlock::CodeBlock() {}

CodeBlock::CodeBlock(CodeBlock* blockPtr, unsigned int prev_depth) : parentPtr(blockPtr), depth(prev_depth + 1) {}

// Needs to pass in trimmed string line.
unsigned int CodeBlock::addLine(string line) {
    bool isSubBlockStart = line.back() == '{';
    bool isSubBlockEnd = line.front() == '}';
    
    unsigned int len = line.length();

    if (!lines.size()) {
        // If input line is the first one to be added,
        // do not check for delegation and add it.
        lines.push_back(line);
        if (len > max_len) {
            max_len = len;
            propagateMaxLen();
        }
        return max_len;
    }

    // If there are other lines in the code block, 
    // check for delegation.
    if (delegateToSubBlocks) {
        // If it needs to be delegated to its sub-block
        if (!isSubBlockStart && isSubBlockEnd) {
            // CASE: }
            // If the end of a block is reached,
            // unset the delegation flag
            if (!subBlocks.back()->delegateToSubBlocks)
                delegateToSubBlocks = false;
        }
        // length of the current line should be larger by 2 than the length of the line of the child
        len = subBlocks.back()->addLine(line) + 2;
    } else {
        if (isSubBlockStart && !isSubBlockEnd) {
            // CASE:  ~ {
            // If the start of a sub-block is reached,
            // set the delegation flag, add the index where the sub-block start, create a new CodeBlock instance
            subBlocksPosArr.push_back(lines.size() - 1);
            subBlocks.push_back(std::make_unique<CodeBlock>(this, depth));
            len = subBlocks.back()->addLine(line) + 2;
            delegateToSubBlocks = true;
        } else if (isSubBlockStart && isSubBlockEnd) {
            // CASE: } ~~ {
            parentPtr->subBlocksPosArr.push_back(parentPtr->lines.size() - 1);
            parentPtr->subBlocks.push_back(std::make_unique<CodeBlock>(parentPtr, parentPtr->getDepth()));
            len = parentPtr->subBlocks.back()->addLine(line) + 2;
        } else {
            lines.push_back(line);
        }
    }

    if (len > max_len) {
        max_len = len;
        propagateMaxLen();
    }

    return max_len;
}

void CodeBlock::propagateMaxLen() {
    // If there are sibling code blocks
    // synchronize max lengths
    if (parentPtr != nullptr){
        for (auto& iter: parentPtr->getSubBlocks()) {
            CodeBlock* siblingPtr = iter.get();
            if (max_len > siblingPtr->max_len) {
                siblingPtr->max_len = max_len;
            } else {
                max_len = siblingPtr->max_len;
            }
        }
    }
}

vector<string>& CodeBlock::getLines() {
    return lines;
}

unsigned int CodeBlock::getLinesSize() {
    return lines.size();
}

vector<std::unique_ptr<CodeBlock>>& CodeBlock::getSubBlocks() {
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

vector<unsigned int> CodeBlock::getMaxLenArr() {
    vector<unsigned int> max_lens;
    CodeBlock* blockPtr = parentPtr;

    max_lens.insert(max_lens.begin(), max_len);
    while (blockPtr != nullptr) {
        max_lens.insert(max_lens.begin(), blockPtr->max_len);
        blockPtr = blockPtr->parentPtr;
    }

    return max_lens;
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
            subBlocks[si++]->print();
            // std::cout << subBlocks[si - 1].max_len << std::endl;
        } 
    }
}