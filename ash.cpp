#include "tclap/CmdLine.h"
#include "tclap/UnlabeledValueArg.h"
#include <filesystem>
#include <iostream>
#include <tclap/ArgException.h>

#include <tree_sitter/api.h>
#include <tree_sitter/tree-sitter-ash.h>

#include "parsing.hpp"

#ifndef PROGRAM_VERSION
#define PROGRAM_VERSION "0.1"
#endif

using namespace TCLAP;
using namespace std::filesystem;

struct AshArgs {
    bool verbose;
    path input;
};

AshArgs parse_args(int argc, char **argv) {
    CmdLine cmd("Test command", ' ', PROGRAM_VERSION);
    SwitchArg verbose("v", "verbose", "Prints more infomation than normally",
                      cmd);
    UnlabeledValueArg<std::string> file("FILE", "The input file", true, "ERROR",
                                        "file", cmd);
    cmd.parse(argc, argv);

    return {verbose.getValue(), path(file.getValue())};
}

void run_ash(AshArgs args) {
    if (args.verbose)
        std::clog << "Starting program" << std::endl;

    if (!exists(args.input)) {
        throw std::runtime_error("Input file does not exist");
    }

    if (args.verbose)
        std::clog << "Reading file " << args.input.string() << std::endl;

    TSTree *tree = fget_asht(args.input);
    ts_tree_delete(tree);

    on_finished_parsing();
}

int main(int argc, char **argv) {
    AshArgs args;
    try {
        args = parse_args(argc, argv);
    } catch (ArgException &e) {
        std::clog << "Error: " << e.what() << std::endl;
        return 1;
    }
    try {
        run_ash(args);
    } catch (std::runtime_error &e) {
        std::clog << "Error: " << e.what() << std::endl;
        return 2;
    }

    return 0;
}
