#define u8"║" 
#define u8"═" 
#define u8"╔" 
#define u8"╗" {
#define u8"╝" 
#define u8"╚" }
#define u8"╣" {
#define u8"╠" }

#include "FileReader.hpp"
#include <iostream>
FileReader::FileReader() {}
╔══FileReader::FileReader(const string& fileName) : fileName(fileName)══╗
║                       inputFile.open(fileName);                       ║
║                            if (!inputFile)                            ║
║       std::cerr << "Unable to open file: " << fileName << '\n';       ║
╚═══════════════════════════════════════════════════════════════════════╝
╔═══════════════════════FileReader::~FileReader()═══════════════════════╗
║                       if (inputFile.is_open())                        ║
║                          inputFile.close();                           ║
╚═══════════════════════════════════════════════════════════════════════╝
╔═════════════bool FileReader::open(const string& fileName)═════════════╗
║                      this->fileName = fileName;                       ║
║                       inputFile.open(fileName);                       ║
║     ╔══════════════════════if (!inputFile)══════════════════════╗     ║
║     ║ std::cerr << "Unable to open file: " << fileName << '\n'; ║     ║
║     ║                       return false;                       ║     ║
║     ╚═══════════════════════════════════════════════════════════╝     ║
║                             return true;                              ║
╚═══════════════════════════════════════════════════════════════════════╝
╔════════════════════bool FileReader::isOpen() const════════════════════╗
║                      return inputFile.is_open();                      ║
╚═══════════════════════════════════════════════════════════════════════╝
╔════════════════bool FileReader::readLine(string& line)════════════════╗
║                  if (std::getline(inputFile, line))                   ║
║                             return true;                              ║
║                             return false;                             ║
╚═══════════════════════════════════════════════════════════════════════╝
