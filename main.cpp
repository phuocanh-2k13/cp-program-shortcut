#include <bits/stdc++.h>
#include "wrapper/wrapper.hpp"
#include "compute/compute.hpp"

namespace fs = std::filesystem;

int main() {
    std::ios::sync_with_stdio(false);

    // GET HOME ENVIRONMENT
    const char* home_env = std::getenv("HOME");
    if (home_env == nullptr) {
        std::cerr << "[ERROR] HOME environment variable is not set" << std::endl;
        return EXIT_FAILURE;
    }

    // CREATE FOLDER PROJECT
    std::string problem_name;
    std::cout << "[001] Enter problem name: ";
    std::cin >> problem_name;
    Folder problem_folder = createFolder(problem_name);
    std::cout << "[001] Successfully created folder: " << problem_folder.name() << std::endl;

    // // CREATE MAIN.CPP FILE
    std::string template_type;
    std::cout << "[002] Enter template type ([other]/leetcode): ";
    std::cin >> template_type;
    
    // ASSIGN TEMPLATE TO MAIN.CPP FILE
    std::string main_cpp_path = problem_folder.name() + "/main.cpp";
    std::string template_path = std::string(home_env) + "/.local/bin/template/template_" + (template_type == "leetcode" ? "leetcode" : "default") + ".cpp"; // PATH TO TEMPLATE FILE
    if (!assignTemplate(template_path, main_cpp_path)) {
        std::cerr << "[ERROR] Failed to assign template file" << std::endl;
        return EXIT_FAILURE;
    }

    // CREATE INPUT, OUTPUT FILES
    std::string IO_name;
    std::cout << "[003] Enter input/output file name (none/filename): ";
    std::cin >> IO_name;
    createIOFiles(IO_name, problem_folder.name());

    // CREATE RUN FILE
    createRunFile(IO_name, problem_folder.name());
    std::cout << "[004] Successfully created run.sh file" << std::endl;

    // GIVE EXECUTION PERMISSION TO RUN FILE
    giveExecutionPermission(problem_folder.name() + "/run.sh");

    // END
    std::cout << "==== COMPLETE ====" << std::endl;

    return 0;
}
