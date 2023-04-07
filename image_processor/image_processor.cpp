#include <iostream>
#include "application.h"

int main(int argc, char* argv[]) {
    try {
        Application app;
        app.Run(argc, argv);
    } catch (...) {
        std::cerr << "program failed\n";
    }
    return 0;
}
