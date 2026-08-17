#pragma once

#include <filesystem>
#include <string>
namespace fs = std::filesystem;

// FOLDER HEADER DECLARE
class Folder {
private:
    fs::path path;

public:
    Folder(const std::string& p);
    std::string name();
};

// FILE HEADER DECLARE
class File {
private:
    fs::path path;
    std::ofstream ofs;

public:
    File(const std::string& p);
    bool assign(const std::string& content);
    std::string name();
};