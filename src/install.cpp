#include <filesystem>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <limits>
#include "../nlohmann/json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

int main() {
    std::ios::sync_with_stdio(false);

    const char* home_env = getenv("HOME");
    if (!home_env) {
        std::cerr << "ERROR: HOME environment variable is not set.\n";
        return EXIT_FAILURE;
    }

    std::string home_str(home_env);
    std::string bin_path = home_str + "/.local/bin";
    std::string bash_path = home_str + "/.bashrc";
    std::string config_line = "export PATH=\"$HOME/.local/bin:$PATH\"";

    // 1. Create folder if it doesn't exist
    try {
        fs::create_directories(bin_path);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error creating directory: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    // CONFIG STEP
    const std::unordered_map<int, std::string> editorMap = {
        {1, "vim"},
        {2, "subl"},
        {3, "code"},
        {4, "nano"},
        {5, "zed"},
        {0, "none"}
    };

    std::cout << "What editor do you use?\n";
    std::cout << "[0] If none of these\n";
    std::cout << "[1] Vim\n";
    std::cout << "[2] Sublime Text\n";
    std::cout << "[3] Visual Studio Code\n";
    std::cout << "[4] Nano\n";
    std::cout << "[5] Zed\n";

    int editor = -1;
    std::string selected_editor = "none";

    if (!(std::cin >> editor)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid input, defaulting to 'none'.\n";
    } else {
        auto it = editorMap.find(editor);
        if (it != editorMap.end()) {
            selected_editor = it->second;
        } else {
            std::cerr << "Unknown option, defaulting to 'none'.\n";
        }
    }

    // CREATE CONFIGURATION FILE
    json configJSON;
    configJSON["editor"] = selected_editor;

    std::ofstream config("config.json");
    if (config.is_open()) {
        config << configJSON.dump(4);
        config.close();
        std::cout << "Success creating config.json file\n";
    }
    else {
        std::cout << "Failed to create config.json\n";
    }

    // 2. Copy files
    try {
        // Copy executable
        if (fs::exists("cp-setup")) {
            fs::copy_file("cp-setup", bin_path + "/cp-setup",
                          fs::copy_options::overwrite_existing);
        } else {
            std::cerr << "Warning: 'cp-setup' file not found in current directory.\n";
        }

        // Copy template folder
        if (fs::exists("template")) {
            fs::copy("template", bin_path + "/template",
                     fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        } else {
            std::cerr << "Warning: 'template' folder not found in current directory.\n";
        }

        // Copy config.json file
        if (fs::exists("config.json")) {
            fs::rename("config.json", bin_path + "/config.json");
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error copying files: " << e.what() << "\n";
    }

    // 3. Add configuration to .bashrc
    if (fs::exists(bash_path)) {
        bool line_exists = false;
        std::ifstream infile(bash_path);

        if (infile.is_open()) {
            std::string line;
            while (std::getline(infile, line)) {
                if (line == config_line) {
                    line_exists = true;
                    break;
                }
            }
            infile.close();
        }

        if (!line_exists) {
            std::ofstream outfile(bash_path, std::ios::app);
            if (outfile.is_open()) {
                outfile << '\n' << config_line << '\n';
                outfile.close();
                std::cout << "Added PATH configuration to .bashrc\n";
            } else {
                std::cerr << "Error: Could not open .bashrc for writing.\n";
            }
        }
    } else {
        std::cout << "Note: .bashrc not found. If you use zsh, please add the PATH manually to .zshrc\n";
    }

    // 4. Update PATH for current process immediately
    const char* current_path = getenv("PATH");
    std::string new_path_value = bin_path + ":" + (current_path ? current_path : "");

    if (setenv("PATH", new_path_value.c_str(), 1) != 0) {
        std::cerr << "Warning: Failed to update PATH for current session.\n";
    }

    // 5. Check if cp-setup is accessible
    int check_result = std::system("command -v cp-setup >/dev/null 2>&1");

    if (check_result == 0) {
        std::cout << "Success: cp-setup installed and available!\n";
    } else {
        std::cerr << "Error: cp-setup installation failed or not in PATH.\n";
        return EXIT_FAILURE;
    }
    return 0;
}