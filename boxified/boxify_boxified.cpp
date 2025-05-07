#define u8"║" 
#define u8"═" 
#define u8"╔" 
#define u8"╗" {
#define u8"╝" 
#define u8"╚" }
#define u8"╣" {
#define u8"╠" }

#include "boxify.hpp"
Boxifier::Boxifier(const std::string path)
╔════════════════════════════════════════════════════════: path(path), fileReader(path)════════════════════════════════════════════════════════╗
║                                                   auto [name, ext] = splitExtension(path);                                                   ║
║                             vector<string> parts = {BOXIFY_DIRECTORY + name.substr(2) + BOXIFY_INDICATOR, ext};                              ║
║                                                  string outputFileName = join(parts, ".");                                                   ║
║                                                       fileWriter.open(outputFileName);                                                       ║
║                                                                 string line;                                                                 ║
║                                       ╔══════════════while (fileReader.readLine(line))═══════════════╗                                       ║
║                                       ║                         trim(line);                          ║                                       ║
║                                       ║                    if (line.size() == 0)                     ║                                       ║
║                                       ║                          continue;                           ║                                       ║
║                                       ║╔══if (line.size() > 2 && line[0] == '/' && line[1] == '/')══╗║                                       ║
║                                       ║║                         continue;                          ║║                                       ║
║                                       ║╚════════════════════════════════════════════════════════════╝║                                       ║
║                                       ║                   codeBlock.addLine(line);                   ║                                       ║
║                                       ╚══════════════════════════════════════════════════════════════╝                                       ║
╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
╔══════════════════════════════════════════════════════════void Boxifier::boxifyAll()══════════════════════════════════════════════════════════╗
║                         std::filesystem::create_directories(std::filesystem::path(BOXIFY_DIRECTORY).parent_path());                          ║
║                                                     fileWriter.writeLine(BOXIFY_MACRO);                                                      ║
║                                                              boxify(codeBlock);                                                              ║
╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
╔═══════════════════════════════════════════════════void Boxifier::boxify(CodeBlock& block)════════════════════════════════════════════════════╗
║                                                                size_t si = 0;                                                                ║
║                                                    vector block_lines = block.getLines();                                                    ║
║                                              vector<unsigned int> lens = block.getMaxLenArr();                                               ║
║╔═════════════════════════════════════════════for (size_t i = 0; i < block.getLinesSize(); ++i)══════════════════════════════════════════════╗║
║║╔══════════════════════════════════════════════════════════if (block.getDepth())═══════════════════════════════════════════════════════════╗║║
║║║                                                          string centered_line;                                                           ║║║
║║║ ╔═══════════════════════════════════if (block_lines[i].front() != '' && block_lines[i].back() == '')═══════════════════════════════════╗ ║║║
║║║ ║                                                delete_curly_brackets(block_lines[i]);                                                ║ ║║║
║║║ ║                                                        trim(block_lines[i]);                                                         ║ ║║║
║║║ ║      centered_line = string(UPPERLEFT) + center_string(block_lines[i], block.getMaxLen() + 2, HORIZONTAL) + string(UPPERRIGHT);      ║ ║║║
║║║ ╠════════════════════════════════else if (block_lines[i].front() == '' && block_lines[i].back() == '')═════════════════════════════════╣ ║║║
║║║ ║                                                delete_curly_brackets(block_lines[i]);                                                ║ ║║║
║║║ ║                                                        trim(block_lines[i]);                                                         ║ ║║║
║║║ ║   centered_line = string(VERTICALRIGHT) + center_string(block_lines[i], block.getMaxLen() + 2, HORIZONTAL) + string(VERTICALLEFT);   ║ ║║║
║║║ ╠════════════════════════════════else if (block_lines[i].front() == '' && block_lines[i].back() != '')═════════════════════════════════╣ ║║║
║║║ ║                                                delete_curly_brackets(block_lines[i]);                                                ║ ║║║
║║║ ║                                                        trim(block_lines[i]);                                                         ║ ║║║
║║║ ║      centered_line = string(LOWERLEFT) + center_string(block_lines[i], block.getMaxLen() + 2, HORIZONTAL) + string(LOWERRIGHT);      ║ ║║║
║║║ ╠═════════════════════════════════════════════════════════════════else═════════════════════════════════════════════════════════════════╣ ║║║
║║║ ║             centered_line = string(VERTICAL) + center_string(block_lines[i], block.getMaxLen() + 2) + string(VERTICAL);              ║ ║║║
║║║ ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝ ║║║
║║║ ╔═══════════════════════════════════════for (unsigned int i = block.getDepth() - 1; i > 0; --i)════════════════════════════════════════╗ ║║║
║║║ ║                                      centered_line = center_string(centered_line, lens[i] + 2);                                      ║ ║║║
║║║ ║                                 centered_line = string(VERTICAL) + centered_line + string(VERTICAL);                                 ║ ║║║
║║║ ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝ ║║║
║║║                                                   fileWriter.writeLine(centered_line);                                                   ║║║
║║╠═══════════════════════════════════════════════════════════════════else═══════════════════════════════════════════════════════════════════╣║║
║║║                                                  fileWriter.writeLine(block_lines[i]);                                                   ║║║
║║╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝║║
║║╔═════════════════════════════while (si < block.getSubBlocksPos().size() && block.getSubBlocksPos()[si] == i)══════════════════════════════╗║║
║║║                                                   boxify(*block.getSubBlocks()[si++]);                                                   ║║║
║║╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝║║
║╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝║
╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
╔══════════════════════════════════════════════════════════════════int main()══════════════════════════════════════════════════════════════════╗
║                                                     ExtensionFinder finder(EXTENSIONS);                                                      ║
║                                             ╔══for (std::string path : finder.getFileNames())══╗                                             ║
║                                             ║             Boxifier boxifier(path);             ║                                             ║
║                                             ║              boxifier.boxifyAll();               ║                                             ║
║                                             ╚══════════════════════════════════════════════════╝                                             ║
║                                                                  return 0;                                                                   ║
╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
