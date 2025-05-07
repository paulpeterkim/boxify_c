#include "FileWriter.hpp"

#include <iostream>
FileWriter::FileWriter(){}

FileWriter::FileWriter(const string& fileName) : fileName(fileName) {
    outputFile.open(fileName);
    if (!outputFile)
        std::cerr << "Unable to write to file: " << fileName << '\n';
}

FileWriter::~FileWriter() {
    if (outputFile.is_open())
        outputFile.close();
}

bool FileWriter::open(const string& fileName) {
    this->fileName = fileName;
    outputFile.open(fileName);
    if (!outputFile){
        std::cerr << "Unable to write to file: " << fileName << '\n';
        return false;
    }
    return true;
}

bool FileWriter::isOpen() const {
    return outputFile.is_open();
}

void FileWriter::writeLine(string& line) {
    outputFile << line << '\n';
}