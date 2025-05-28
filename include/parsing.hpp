#ifndef PARSING_HPP
#define PARSING_HPP

#include <filesystem>
#include <string>
#include <tree_sitter/api.h>
#include <tree_sitter/tree-sitter-ash.h>

using namespace std::filesystem;

TSTree *get_asht(std::string);
TSTree *fget_asht(path);
void on_finished_parsing();

#endif
