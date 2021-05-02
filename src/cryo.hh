#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <regex>
#include <filesystem>

namespace cryo {

#include <stdio.h>
#include <getopt.h>

#include "result.hh"

#define CRYO_APPLICATION_NAME   "CRyo"
#define CRYO_VERSION            "0.0.1"
#define CRYO_HELP_STRING "\
Usage:\n\
    cryo [options] <path>\n\
Options:\n\
    -h --help           Display this information.\n\
    -v --version        Display the version number.\n\
    -i --import <path>  Specify target for import files.\n\
    -e --export <path>  Specify target for export files.\n\
    -d --disable-docs   Disable generate documents.\n\
    -t --disable-tests  Disable generate tests.\n"

#define CRYO_CXX_EXTENSION_REGEX "(\\.c|\\.cc|\\.cxx|\\.cpp|\\.h|\\.hh|\\.hxx|\\.hpp)$"

    class Object{
    private:
        class Arguments {
        private:
            int arguments_count;
            char** arguments_values;
            char* import_path;
            char* export_path;
        public:
            Arguments(int argc, char *argv[]);
            ~Arguments();
            bool validate(std::vector<std::string>& paths, std::string& exportPath);
            bool get_src_path();
        };
        class Generator {
        public:
            Generator();
            ~Generator();
            bool generate(std::vector<std::string>& paths, std::string& exportPath);
        };
        std::unique_ptr<Arguments> arguments;
        std::unique_ptr<Generator> generator;
        std::vector<std::string> paths;
        std::string export_path;

    public:
        Object(int argc, char *argv[]);
        ~Object();
        bool validate();
        bool generate();
    };
}

cryo::Object::Arguments::Arguments(int argc, char *argv[]) {
    this->arguments_count = argc;
    this->arguments_values = argv;
    this->import_path = NULL;
    this->export_path = NULL;
}
cryo::Object::Arguments::~Arguments() {
    return;
}

bool cryo::Object::Arguments::get_src_path() {
    return true;
}

bool cryo::Object::Arguments::validate(std::vector<std::string>& paths, std::string& exportPath) {

    int help_status = 0;
    int version_status = 0;
    int import_status = 0;
    int export_status = 0;
    int disable_docs_status = 0;
    int disable_tests_status = 0;

    struct option longopts[] = {
        { "help",          no_argument,        NULL, 'h' },
        { "version",       no_argument,        NULL, 'v' },
        { "import",        required_argument,  NULL, 'i' },
        { "export",        required_argument,  NULL, 'e' },
        { "disable-docs",  no_argument,        NULL, 'd' },
        { "disable-tests", no_argument,        NULL, 't' },
        { 0,               0,                  0,     0  },
    };

    int opt;
    int longindex;
    while ((opt = getopt_long(this->arguments_count, this->arguments_values, "i:e:hvdt", longopts, &longindex)) != -1) {
        switch (opt) {
        case 'h':
            help_status = 1;
            break;
        case 'v':
            version_status = 1;
            break;
        case 'i':
            import_status = 1;
            this->import_path = optarg;
            break;
        case 'e':
            export_status = 1;
            this->export_path = optarg;
            break;
        case 'd':
            disable_docs_status = 1;
            break;
        case 't':
            disable_tests_status = 1;
            break;
        default:
            return 1;
        }
    }

    if(help_status != 0) {
        printf(CRYO_HELP_STRING);
        return true;
    } else if(version_status != 0) {
        printf("%s (%s) %s\n", this->arguments_values[0], CRYO_APPLICATION_NAME, CRYO_VERSION);
        return true;
    } else if(import_status != 0 && export_status != 0) {
        exportPath = std::string(this->export_path);

        std::string open_path = std::string(import_path);
        std::ifstream ifs(open_path);
        std::regex re(CRYO_CXX_EXTENSION_REGEX);
        std::smatch m;

        // TODO: check a file or directory

        if (ifs.is_open()) {
            for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(open_path)) {
                std::string str = entry.path().string();
                if (std::regex_search(str, m, re)) {
                    paths.push_back( entry.path().string() );
                }
            }
        } else {
            printf("%s: import path is not found.\n", this->arguments_values[0]);
            return false;
        }

        if(paths.empty()) {
            printf("%s: c source is not found. no work to do.\n", this->arguments_values[0]);
            return true;
        }
        return true;
    } else if(import_status != 1 || export_status != 1) {
        printf("%s: the options is required: [import, export]\n", this->arguments_values[0]);
        return false;
    }
    printf("%s: use the --help option for usage information.\n", this->arguments_values[0]);
    return false;
}

cryo::Object::Generator::Generator() {
    return;
}
cryo::Object::Generator::~Generator() {
    return;
}
bool cryo::Object::Generator::generate(std::vector<std::string>& importPaths, std::string& exportPath) {

    int hash_seed = 0;

    std::smatch m;
    if (!std::regex_search(exportPath, m, std::regex("/$"))) {
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
        std::regex cxx_code_block_begin("```.*(\\.|)(c|cc|cxx|cpp|h|hh|hxx|hpp)"); // or '~'
        std::regex cxx_code_block_end("```"); // or '~'
        std::regex re("^(\\s*)(\\*)(\\s|)(.*)");

        // TODO: extension from markdown
        // std::string extension = "";

        while (getline(ifs, str)) {
            if(std::regex_search(str, m, re)) {
                if(std::regex_search(str, m, cxx_code_block_begin)) {
                    if (is_cxx_code_block == false) {
                        is_cxx_code_block = true;
                        hash_seed++;
                    } else {
                        printf("parse error.");
                        return 0;
                    }
                } else if(std::regex_search(str, m, cxx_code_block_end)) {
                    if (is_cxx_code_block == true) {
                        // export file
                        // TODO: Make file names easier to understand.
                        std::string export_file = exportPath + std::to_string(hash_seed) + ".cc";
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
                    if(is_cxx_code_block == true && std::regex_search(str, m, re)) {
                        export_string = export_string + m[4].str() + "\n";
                    }
                }
            }
        }
    }
    return true;
}

cryo::Object::Object(int argc, char *argv[]) {
    this->arguments = std::make_unique<Arguments>(argc, argv);
    this->generator = std::make_unique<Generator>();
    this->paths = {};
}

cryo::Object::~Object() {
    std::vector<std::string>().swap(this->paths);
    return;
}

bool cryo::Object::validate() {
    return this->arguments->validate(this->paths, this->export_path);
}

bool cryo::Object::generate() {
    return this->generator->generate(this->paths, this->export_path);
}
