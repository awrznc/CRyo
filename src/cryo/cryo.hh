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
#define CRYO_VERSION            "0.0.3"
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

#define CRYO_CXX_EXTENSION_REGEX "(\\.cc|\\.cxx|\\.cpp|\\.c|\\.hh|\\.hxx|\\.hpp|\\.h)$"

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
            bool validate(std::vector<std::string>& importPaths, std::string& importPath, std::string& exportPath);
            bool get_src_path();
        };
        class Generator {
        public:
            Generator();
            ~Generator();
            bool generate(std::vector<std::string>& importPaths, std::string& importPath, std::string& exportPath);
        };
        std::unique_ptr<Arguments> arguments;
        std::unique_ptr<Generator> generator;
        std::vector<std::string> import_paths;
        std::string import_path;
        std::string export_path;

    public:
        Object(int argc, char *argv[]);
        ~Object();
        bool validate();
        bool generate();
    };
}
