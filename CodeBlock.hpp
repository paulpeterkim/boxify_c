#ifndef CODEBLOCK_HPP
#define CODEBLOCK_HPP

#include <string>
#include <vector>

using std::vector;
using std::string;

class CodeBlock {
private:
    vector<string> lines;
    vector<unsigned int> subBlocksPosArr; // Stores indices of the vector "lines" which after such indices, sub code blocks follow.
    vector<CodeBlock> subBlocks;
    bool delegateToSubBlocks = false; // A flag when set, transfers input line to its sub code blocks.
    unsigned int depth = 0; // Depth of current code block
    unsigned int max_len = 0; 
public:
    CodeBlock();
    // Constructor for subblocks.
    CodeBlock(int depth);
    // Adds line of string. Returns max length of the current code block.
    unsigned int addLine(string line);
    vector<string>& getLines();
    unsigned int getLinesSize();
    vector<CodeBlock>& getSubBlocks();
    vector<unsigned int>& getSubBlocksPos();
    unsigned int getDepth();
    unsigned int getMaxLen();
    void print();
};

#endif