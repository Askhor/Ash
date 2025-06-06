#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <string>
#include <vector>

#include "ast/common_ast.hpp"
#include "ast/fields.hpp"

namespace ast {

struct Definition : Node {
    sptr<ast::Identifier> name;
    sptr<ast::Identifier> supertype;

    virtual void pretty_print(PrettyStream &out) {
        out.new_line();
        out << "Pretty printing not implemented for definitions";
    }
};

struct TokenDefinition final : Definition {
    sptr<ast::Regex> regex;

    TokenDefinition() {
    }

    NODE_TYPE_NAME("Token")
    NODE_TYPE_GETTER(TOKEN)

    virtual void pretty_print(PrettyStream &out) {
        out.new_line();
        out << Color::ORANGE << "token " << Color::NONE;
        name->pretty_print(out);
        out << " ";
        regex->pretty_print(out);
    }
};

struct AbstractNodeDefinition final : Definition {
    NODE_TYPE_NAME("Abstract Node Definition")
    NODE_TYPE_GETTER(ABSTRACT_NODE)
    virtual void pretty_print(PrettyStream &out) {
        out.new_line();
        out << Color::ORANGE << "abstract node " << Color::NONE;
        name->pretty_print(out);
    }
};

struct NodeDefinition final : Definition {
    NODE_TYPE_NAME("Node Definition")
    NODE_TYPE_GETTER(NODE)
    std::vector<sptr<Field>> fields;

    virtual void pretty_print(PrettyStream &out) {
        out.new_line();
        out.new_line();
        out << Color::ORANGE << "node " << Color::NONE;
        name->pretty_print(out);
        out << " {";

        out.indent++;
        for (sptr<Field> field : fields) {
            field->pretty_print(out);
        }
        out.indent--;

        out.new_line();
        out << "}";

        out.new_line();
    }
};

} // namespace ast

#endif
