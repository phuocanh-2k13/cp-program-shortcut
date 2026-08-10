#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

// FOLDER WRAPPER CLASS
class Folder {
    fs::path path;

    public:
    Folder(const std::string& p) : path(p) {
        fs::create_directory(path);
        if (!fs::exists(path)) {
            std::cerr << "[ERROR] Failed to create directory: " << path << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    std::string name() {
        return path.filename().string();
    }
};

// FILE WRAPPER CLASS
class File {
    fs::path path;
    std::ofstream ofs;

    public:
    File(const std::string& p) : path(p), ofs(p) {
        if (!ofs.is_open()) {
            std::cerr << "[ERROR] Failed to create file: " << path << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    bool assign_to_file(const std::string& content) {
        ofs << content;
        return ofs.good();
    }

    std::string name() {
        return path.filename().string();
    }

    ~File() {
        ofs.close();
    }
};