#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <tree_sitter/api.h>
#include <tree_sitter/tree-sitter-ash.h>
#include <vector>

struct Definition {};

namespace ast {
struct File {
    std::vector<Definition> definitions;

    File(TSNode node) {
    }
};

struct Identifier {};

} // namespace ast

#endif
