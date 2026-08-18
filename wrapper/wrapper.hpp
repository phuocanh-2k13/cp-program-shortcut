#pragma once

#include <filesystem>
#include <string>
#include <fstream>
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
    // Constructor
    explicit File(const std::string& p);

    // Disable copying
    File(const File&) = delete;
    File& operator=(const File&) = delete;

    // Enable moving
    File(File&&) noexcept = default;
    File& operator=(File&&) noexcept = default;

    bool assign(const std::string& content);
    std::string name();
    ~File() = default;
};
