#ifndef FIELDS_HPP
#define FIELDS_HPP

#include "ast/common_ast.hpp"
#include "ast/regex.hpp"

namespace ast {

struct Field : Node {};

struct RegexField final : Field {
    sptr<ast::Regex> regex;

    RegexField() {
    }

    NODE_TYPE_NAME("Regex Field")
    NODE_TYPE_GETTER(REGEX_FIELD)

    virtual void pretty_print(PrettyStream &out) {
        out.new_line();
        regex->pretty_print(out);
    }
};

enum class NodeFieldModifier { NONE, OPTIONAL, ARRAY };

struct NodeField final : Field {
    NodeFieldModifier modifier;
    sptr<Identifier> name;
    sptr<Identifier> type;

    NodeField() {
    }

    NODE_TYPE_NAME("Node Field")
    NODE_TYPE_GETTER(NODE_FIELD)

    virtual void pretty_print(PrettyStream &out) {
        out.new_line();

        switch (modifier) {
        case NodeFieldModifier::NONE:
            break;
        case NodeFieldModifier::OPTIONAL:
            out << Color::ORANGE << "optional " << Color::NONE;
            break;
        case NodeFieldModifier::ARRAY:
            out << Color::ORANGE << "array " << Color::NONE;
            break;
        }

        name->pretty_print(out);
        out << Color::ORANGE << " is " << Color::NONE;
        type->pretty_print(out);
    }
};

} // namespace ast

#endif
