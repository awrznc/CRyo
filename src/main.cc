#include "cryo.hh"

// The entry point.
int main(int argc, char *argv[]) {

    // Initialize CRyo.
    const std::shared_ptr<cryo::Object> cryo(new cryo::Object(argc, argv));

    // Validate Arguments.
    if (!cryo->validate()) return 1;

    // Generate Tests.
    if (!cryo->generate()) return 2;

    // SUCCESS
    return 0;
}
