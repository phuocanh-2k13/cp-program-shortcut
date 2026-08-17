#include "wrapper.hpp"

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

// FOLDER WRAPPER CLASS
Folder::Folder(const std::string& p) : path(p) {
    fs::create_directory(path);
    if (!fs::exists(path)) {
        std::cerr << "[ERROR] Failed to create directory: " << path << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
std::string Folder::name() {
    return path.filename().string();
}


// FILE WRAPPER CLASS
File::File(const std::string& p) : path(p), ofs(p) {
    if (!ofs.is_open()) {
        std::cerr << "[ERROR] Failed to create file: " << path << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
bool File::assign(const std::string& content) {
    ofs << content;
    return ofs.good();
}
std::string File::name() {
    return path.filename().string();
}
File::~File() {
    ofs.close();
}