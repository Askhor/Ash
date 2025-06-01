#ifndef TSPARSING_HPP
#define TSPARSING_HPP

#include <filesystem>
#include <string>
#include <tree_sitter/api.h>
#include <tree_sitter/tree-sitter-ash.h>

using namespace std::filesystem;

std::string read_file(path);
TSTree *get_asht(std::string);
void ts_debug_print(std::string source, TSTree *);
void on_finished_parsing();

#endif
