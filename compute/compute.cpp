#include "../wrapper/wrapper.hpp"
#include <iostream>
#include <vector>

Folder createFolder(const std::string& path) {
    Folder folder(path);
    return folder;
}

File createFile(const std::string& path) {
    File file(path);
    return file;
}

bool assignTemplate(const std::string& template_path, const std::string& file_path) {
    try {
        if (!fs::exists(template_path)) {
            std::cerr << "[ERROR] Template file does not exist: " << template_path << ". No need to assign templates" << std::endl;
            return false;
        }
        else {
            fs::copy_file(template_path, file_path, fs::copy_options::overwrite_existing);
            std::cout << "[002] Successfully asssign template file" << std::endl;
            return true;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "[ERROR] Exception occurred: " << e.what() << std::endl;
        return false;
    }
}

std::pair<File, File> createIOFiles(const std::string& file_name, const std::string& folder_path) {
    std::string input_file_path = folder_path + "/" + (file_name != "none" ? file_name : "input") + ".txt";
    std::string output_file_path = folder_path + "/" + (file_name != "none" ? file_name : "output") + ".txt";
    File input_file(input_file_path);
    File output_file(output_file_path);
    return {input_file, output_file};
}

File createRunFile(const std::string& IO_name, const std::string& folder_path) {
    std::string run_file_path = folder_path + "/" + "run.sh";
    File run_file(run_file_path);
    std::vector<std::string> commands({
        "#!/bin/bash",
        "if [ \"$1\" == \"CHECK\" ]; then",
        "echo \"--- Checking for differences between example output and your output ---\"",
        "g++ -O2 -funroll-loops -std=c++17 -Wall -Wextra main.cpp -o main",
        "./main < " + IO_name + ".txt > user_output.txt",
        "echo \"--- Difference between example output and your output ---\"",
        "diff -y --suppress-common-lines " + IO_name + ".txt user_output.txt",
        "else",
        "g++ -O2 -funroll-loops -std=c++17 -Wall -Wextra main.cpp -o main",
        "./main",
        "fi"
    });
    std::string run_file_content;
    for (const auto& command : commands) {
        run_file_content += command + "\n";
    }
    run_file.assign(run_file_content);
    return run_file;
};

bool giveExecutionPermission(const std::string& run_path) {
    std::string chmod_command = "chmod +x " + run_path;
    if (std::system(chmod_command.c_str()) != 0) {
        std::cerr << "[ERROR] Failed to give execution permission to run.sh file, run it yourself" << std::endl;
        return false;
    }
    return true;
};