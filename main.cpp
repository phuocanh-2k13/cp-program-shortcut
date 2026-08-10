#include <bits/stdc++.h>
#include <wrapper.hpp>

namespace fs = std::filesystem;


int main() {
    std::ios::sync_with_stdio(false);

    // CREATE FOLDER PROJECT
    std::string problem_name;
    std::cout << "[001] Enter problem name: ";
    std::cin >> problem_name;
    Folder problem_folder(problem_name);
    std::cout << "[001] Successfully created folder: " << problem_folder.name() << std::endl;

    // CREATE MAIN.CPP FILE
    std::string main_cpp_path = problem_folder.name() + "/main.cpp";
    File main_cpp(main_cpp_path);
    try {
        if (!fs::exists("template/main.cpp")) {
            std::cerr << "[ERROR] Template file does not exist: template/main.cpp. No need to assign templates" << std::endl;
        }
        else {
            fs::copy_file("template/main.cpp", main_cpp_path, fs::copy_options::overwrite_existing);
            std::cout << "[002] Successfully created main.cpp file" << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "[ERROR] Exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // CREATE INPUT, OUTPUT FILES
    std::string input_file_path = problem_folder.name() + "/input.txt";
    std::string output_file_path = problem_folder.name() + "/output.txt";
    File input_file(input_file_path);
    File output_file(output_file_path);
    std::cout << "[003] Successfully created input.txt and output.txt files" << std::endl;

    // CREATE RUN FILE
    std::string run_file_path = problem_folder.name() + "/run.sh";
    File run_file(run_file_path);
    std::string run_file_content = "g++ -O2 -funroll-loops -std=c++17 -Wall -Wextra main.cpp -o main\n./main\necho \"--- Difference between example output and your output ---\"\ndiff -y --suppress-common-lines output.txt user_output.txt";
    run_file.assign_to_file(run_file_content);
    std::cout << "[004] Successfully created run.sh file" << std::endl;

    // GIVE EXECUTION PERMISSION TO RUN FILE
    std::string chmod_command = "chmod +x " + run_file_path;
    if (std::system(chmod_command.c_str()) != 0) {
        std::cerr << "[ERROR] Failed to give execution permission to run.sh file, run it yourself" << std::endl;
        return EXIT_FAILURE;
    }

    // END
    std::cout << "==== COMPLETE ====" << std::endl;

    return 0;
}