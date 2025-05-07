#ifndef EXTENSION_FINDER_HPP
#define EXTENSION_FINDER_HPP

#include <filesystem>
#include <string>
#include <vector>
#include <regex>

using std::string;
using std::vector;

namespace fs = std::filesystem;

class ExtensionFinder {
private:
    string target_extension_pattern;
    vector<string> results;
    string cur_path = "./";

public:
    ExtensionFinder(string pattern);

    ExtensionFinder(string pattern, string path);

    ExtensionFinder(string pattern, vector<string> &results, string path);

    ExtensionFinder& findAll();

    vector<string> getFileNames();
};

#endif