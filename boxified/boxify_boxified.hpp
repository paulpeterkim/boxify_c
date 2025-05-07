#define u8"║" 
#define u8"═" 
#define u8"╔" 
#define u8"╗" {
#define u8"╝" 
#define u8"╚" }
#define u8"╣" {
#define u8"╠" }

#ifndef BOXIFY_HPP
#define BIXIFY_HPP
#include <string>
#include <iostream>
#include <filesystem>
#include "ExtensionFinder.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "CodeBlock.hpp"
#include "utils.hpp"
#define NL '\n'
#define LINE "===========================================================\n"
#define EXTENSIONS R"(\b\w+\.c\b|\b\w+\.cpp\b|\b\w+\.cc\b|\b\w+\.cxx\b|\b\w+\.h\b|\b\w+\.hpp\b)"
#define VERTICAL u8"\u2551"
#define HORIZONTAL u8"\u2550"
#define UPPERLEFT u8"\u2554"
#define UPPERRIGHT u8"\u2557"
#define LOWERRIGHT u8"\u255D"
#define LOWERLEFT u8"\u255A"
#define VERTICALLEFT u8"\u2563"
#define VERTICALRIGHT u8"\u2560"
#define BOXIFY_MACRO "#define u8\"\u2551\" \n#define u8\"\u2550\" \n#define u8\"\u2554\" \n#define u8\"\u2557\" {\n#define u8\"\u255D\" \n#define u8\"\u255A\" }\n#define u8\"\u2563\" {\n#define u8\"\u2560\" }\n"
#define BOXIFY_DIRECTORY "./boxified/"
#define BOXIFY_INDICATOR "_boxified"
╔══════════class Boxifier═══════════╗
║             private:              ║
║         std::string path;         ║
║      FileReader fileReader;       ║
║      FileWriter fileWriter;       ║
║       CodeBlock codeBlock;        ║
║       vector<string> lines;       ║
║              public:              ║
║ Boxifier(const std::string path); ║
║         void boxifyAll();         ║
║  void boxify(CodeBlock& block);   ║
╚═════════════════;═════════════════╝
#endif
