#include "cryo.hh"

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

bool cryo::Object::Arguments::validate(std::vector<std::string>& importPaths, std::string& importPath, std::string& exportPath) {

    int help_status = 0;
    int version_status = 0;
    int import_status = 0;
    int export_status = 0;

    struct option longopts[] = {
        { "help",          no_argument,        NULL, 'h' },
        { "version",       no_argument,        NULL, 'v' },
        { "import",        required_argument,  NULL, 'i' },
        { "export",        required_argument,  NULL, 'e' },
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
        importPath = std::string(this->import_path);
        exportPath = std::string(this->export_path);

        std::string open_path = std::string(import_path);
        std::ifstream ifs(open_path);
        std::regex re(CRYO_CXX_EXTENSION_REGEX);
        std::smatch match;

        if (ifs.is_open()) {
            if (std::filesystem::is_directory(open_path)) {
                for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(open_path)) {
                    std::string str = entry.path().string();
                    if (std::regex_search(str, match, re)) {
                        importPaths.push_back( entry.path().string() );
                    }
                }
            } else {
                std::string str = open_path;
                if (std::regex_search(str, match, re)) {
                    importPaths.push_back( open_path );
                }
            }
        } else {
            printf("%s: import path is not found.\n", this->arguments_values[0]);
            return false;
        }

        if(importPaths.empty()) {
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



cryo::Object::Object(int argc, char *argv[]) {
    this->arguments = std::make_unique<Arguments>(argc, argv);
    this->generator = std::make_unique<Generator>();
    this->import_paths = {};
    this->import_path = "";
    this->export_path = "";
}

cryo::Object::~Object() {
    std::vector<std::string>().swap(this->import_paths);
    return;
}

bool cryo::Object::validate() {
    return this->arguments->validate(this->import_paths, this->import_path, this->export_path);
}

bool cryo::Object::generate() {
    return this->generator->generate(this->import_paths, this->import_path, this->export_path);
}
