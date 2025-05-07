#define u8"║" 
#define u8"═" 
#define u8"╔" 
#define u8"╗" {
#define u8"╝" 
#define u8"╚" }
#define u8"╣" {
#define u8"╠" }

#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP
#include <fstream>
#include <string>
using std::string;
using std::ofstream;
╔══════════class FileWriter═══════════╗
║              private:               ║
║          string fileName;           ║
║        ofstream outputFile;         ║
║               public:               ║
║            FileWriter();            ║
║ FileWriter(const string& fileName); ║
║           ~FileWriter();            ║
║ bool open(const string& fileName);  ║
║        bool isOpen() const;         ║
║ void writeLine(const string& line); ║
╚══════════════════;══════════════════╝
#endif
