#include "boxify.hpp"

int main() {
    ExtensionFinder finder(EXTENSIONS);
    
    
    for (std::string path : finder.getFileNames()) {
        Boxifier boxifier(path);
        boxifier.boxifyAll();
    }

    return 0; 
}