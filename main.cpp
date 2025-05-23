#include "tclap/CmdLine.h"
#include <iostream>

#ifndef PROGRAM_VERSION
#define PROGRAM_VERSION "0.1"
#endif

using namespace TCLAP;

int main(int argc, char **argv) {
    CmdLine cmd("Test command", ' ', PROGRAM_VERSION);
    cmd.parse(argc, argv);

    std::cout << "Hello, World!" << std::endl;
}
