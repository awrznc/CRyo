#include "cryo.hh"

cryo::Object::Generator::Generator() {
    return;
}
cryo::Object::Generator::~Generator() {
    return;
}

bool cryo::Object::Generator::generate(std::vector<std::string>& importPaths, std::string& importPath, std::string& exportPath) {

    std::smatch match;
    if (!std::regex_search(exportPath, match, std::regex("/$"))) {
        exportPath = exportPath + "/";
    }

    for (const auto& path : importPaths) {

        std::cout << "[INFO] import: " << path << std::endl;

        // mkdir -p {exportPath}
        std::filesystem::create_directories(exportPath);

        // load file.
        std::ifstream ifs(path);
        if (ifs.fail()) {
            std::cerr << "Failed to open file." << std::endl;
            return -1;
        }

        // analyze string
        bool is_cxx_code_block = false;
        std::string str;

        std::string export_string("");

        // TODO: add ~~~ pattern
        std::regex cxx_code_block_begin("```(\\.|)(c+|cxx|cpp|h+|hxx|hpp)"); // or '~'
        std::regex cxx_code_block_end("```"); // or '~'
        std::regex re("^(\\s*)(\\*)(\\s|)(.*)");

        std::string export_directory_path = "";
        std::string extension = "";

        unsigned int line_number = 0;
        unsigned int current_line_number = 0;

        while (getline(ifs, str)) {
            line_number++;
            if(std::regex_search(str, match, re)) {
                if(std::regex_search(str, match, cxx_code_block_begin)) {
                    extension = match[2].str();

                    std::string export_file_path(path);
                    export_directory_path = std::regex_replace(export_file_path, std::regex(importPath), exportPath);
                    std::filesystem::create_directories(export_directory_path);

                    if (is_cxx_code_block == false) {
                        is_cxx_code_block = true;
                        current_line_number = line_number;
                    } else {
                        printf("parse error.");
                        return 0;
                    }
                } else if(std::regex_search(str, match, cxx_code_block_end)) {
                    if (is_cxx_code_block == true) {

                        // export file
                        std::string export_file = export_directory_path + "/" + std::to_string(current_line_number) + "." + extension;
                        std::cout << "[INFO] export: " << export_file << std::endl;
                        std::ofstream outputfile(export_file.c_str());
                        outputfile << export_string;
                        outputfile.close();

                        // reset
                        export_string = "";
                        is_cxx_code_block = false;
                    } else {
                        printf("parse error.");
                        return 0;
                    }
                } else {
                    if(is_cxx_code_block == true && std::regex_search(str, match, re)) {
                        export_string = export_string + match[4].str() + "\n";
                    }
                }
            }
        }
    }
    return true;
}
