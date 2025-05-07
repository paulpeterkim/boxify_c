#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <fstream>
#include <string>

using std::string;
using std::ifstream;

class FileReader {
private:
    string fileName;
    ifstream inputFile;
public:
    FileReader();

    FileReader(const string& fileName);

    ~FileReader();

    bool open(const string& fileName);

    bool isOpen() const;

    bool readLine(string& line);
};


#endif