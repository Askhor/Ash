#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <string>
#include <tree_sitter/api.h>
#include <tree_sitter/tree-sitter-ash.h>
#include <vector>

#include "ast/definitions.hpp"

namespace ast {
struct File final : Node {
    std::vector<sptr<Definition>> definitions;

    File() {
    }

    NODE_TYPE_NAME("File")
    NODE_TYPE_GETTER(FILE)

    virtual void pretty_print(PrettyStream &out) {
        for (sptr<Definition> def : definitions) {
            def->pretty_print(out);
        }
    }
};

} // namespace ast

#endif
