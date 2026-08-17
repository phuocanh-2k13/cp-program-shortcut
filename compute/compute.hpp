#pragma once

#include <string>
#include <vector>
#include "../wrapper/wrapper.hpp"

Folder createFolder(const std::string& path);
File createFile(const std::string& path);
bool assignTemplate(const std::string& template_path, const std::string& file_path, const std::string& template_type);
std::pair<File, File> createIOFiles(const std::string& folder_path);
File createRunFile(const std::string& IO_name, const std::string& folder_path);
bool giveExecutionPermission(const std::string& run_path);

