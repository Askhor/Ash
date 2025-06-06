#ifndef REGEX_HPP
#define REGEX_HPP

#include "common_ast.hpp"
#include <string>

namespace ast {
struct Regex : Node {
    std::string value;

    Regex() {
    }

    NODE_TYPE_NAME("Regex")
    NODE_TYPE_GETTER(REGEX)

    Regex(std::string value) {
        this->value = value;
    }

    virtual void pretty_print(PrettyStream &out) {
        out << Color::DARK_GREEN << "|" << value << Color::NONE;
    }
};
} // namespace ast

#endif
