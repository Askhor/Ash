#ifndef PASS_MANAGER_HPP
#define PASS_MANAGER_HPP

#include <tree_sitter/api.h>

#include "ast/ast.hpp"

void run_passes(std::string src, TSTree *, int dump_level);

#endif
