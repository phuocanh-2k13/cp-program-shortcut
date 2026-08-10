#include <bits/stdc++.h>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

// FOLDER WRAPPER CLASS
class Folder {
    fs::path path;

    public:
    Folder(const std::string& p) : path(p) {
        fs::create_directory(path);
        if (!fs::exists(path)) {
            std::cerr << "Failed to create directory: " << path << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    std::string name() {
        return path.filename().string();
    }
};

int main() {
    std::ios::sync_with_stdio(false);


    return 0;
}