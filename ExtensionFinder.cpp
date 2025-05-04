#include "ExtensionFinder.hpp"

// Contructor definition
ExtensionFinder::ExtensionFinder(string pattern) 
    : target_extension_pattern(pattern) {}

ExtensionFinder::ExtensionFinder(string pattern, string path) 
    : target_extension_pattern(pattern), cur_path(path)
    {}

ExtensionFinder::ExtensionFinder(string pattern, vector<string> &results, string path) 
    : target_extension_pattern(pattern), results(results), cur_path(path)
    {}

// Method implementation
ExtensionFinder& ExtensionFinder::findAll() {

    std::regex c_extension_re(target_extension_pattern);

    for (const auto& entry: fs::directory_iterator(cur_path)) {
        string path = string(entry.path());
        if (std::regex_search(path, c_extension_re)) {
            results.push_back(path);
        }
    }

    return *this;
}

vector<string> ExtensionFinder::getFileNames() {
    if (!results.size())
        findAll();
    return results;
}