#ifndef CODEBLOCK_HPP
#define CODEBLOCK_HPP

#include <string>
#include <vector>

#include "FileReader.hpp"

using std::vector;
using std::string;

class CodeBlock {
private:
    FileReader& fp;
    vector<string> lines;
    vector<CodeBlock> subBlocks;
    int depth = 0;
public:
    // Contructor for main code block.
    CodeBlock(FileReader& fp);
    // Constructor for subblocks.
    CodeBlock(FileReader& fp, string line);
    void print();
};

#endif