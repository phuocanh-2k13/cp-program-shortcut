#include <iostream>
#include <string>
#include "../wrapper/wrapper.hpp"
#include "../compute/compute.hpp"
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

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
    std::getline(std::cin, problem_name);
    Folder problem_folder = createFolder(problem_name);
    std::cout << "[001] Successfully created folder: " << problem_folder.name() << std::endl;

    // // CREATE MAIN.CPP FILE
    std::string template_type;
    std::cout << "[002] Enter template type (Default/leetcode): ";
    std::getline(std::cin, template_type);

    // ASSIGN TEMPLATE TO MAIN.CPP FILE
    std::string main_cpp_path = problem_folder.name() + "/main.cpp";
    std::string template_path;
    # ifdef DEBUG
    template_path = std::string("./template/template_") + (template_type == "leetcode" ? "leetcode" : "default") + ".cpp";
    #else
    template_path = std::string(home_env) + "/.local/bin/template/template_" + (template_type == "leetcode" ? "leetcode" : "default") + ".cpp";
    #endif
    if (!assignTemplate(template_path, main_cpp_path))
        std::cerr << "[ERROR] Failed to assign template file" << std::endl;

    // CREATE INPUT, OUTPUT FILES
    std::string IO_name = "default";
    std::cout << "[003] Enter input/output file name (Enter if default/filename): ";

    std::string temp;
    std::getline(std::cin, temp);
    if (!temp.empty()) IO_name = temp;

    createIOFiles(IO_name, problem_folder.name());

    // CREATE RUN FILE
    createRunFile(IO_name, problem_folder.name());
    std::cout << "[004] Successfully created run.sh file" << std::endl;

    // GIVE EXECUTION PERMISSION TO RUN FILE
    giveExecutionPermission(problem_folder.name() + "/run.sh");

    // END
    std::cout << "==== COMPLETE ====" << std::endl;

    // OPEN FOLDER, OR CODE???
    std::ifstream configFile(std::string(home_env) + "/.local/bin/config.json");
    json config;
    configFile >> config;

    std::string editorCmd = config["editor"];
    std::string runCmd;
    if (editorCmd == "subl" || editorCmd == "code" || editorCmd == "zed") {
        runCmd = editorCmd + " " + problem_name;
    }
    else if (editorCmd != "none") {
        runCmd = editorCmd + " " + problem_name + "/" + "main.cpp";
    }
    
    if (editorCmd != "none") system(runCmd.c_str());

    return 0;
}
