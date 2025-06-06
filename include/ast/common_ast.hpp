#ifndef COMMON_AST_HPP
#define COMMON_AST_HPP

#include <iostream>
#include <string>

#include "shared_pointers.hpp"
#include "tcolor.hpp"

#define NODE_TYPE_GETTER(the_type)                                             \
    virtual Type get_type() {                                                  \
        return Type::the_type;                                                 \
    }

#define NODE_TYPE_NAME(the_type_name)                                          \
    virtual std::string type_name() {                                          \
        return the_type_name;                                                  \
    }

namespace ast {

enum class Type {
    IDENTIFIER,
    REGEX,
    FILE,
    TOKEN,
    ABSTRACT_NODE,
    NODE,
    NODE_FIELD,
    REGEX_FIELD,
    ERROR
};

struct PrettyStream final {
    std::ostream *out;
    int indent = 0;
    bool use_color = true;

    PrettyStream(std::ostream *out) {
        this->out = out;
    }

    template <typename T> PrettyStream &operator<<(T obj) {
        *out << obj;
        return *this;
    }

    PrettyStream &operator<<(Color c) {
        if (use_color) {
            *out << c;
        }
        return *this;
    }

    void new_line() {
        *out << std::endl;
        for (int i = 0; i < indent; i++) {
            *out << "    ";
        }
    }
};

struct Node {
    virtual void pretty_print(PrettyStream &out) {
        out << "N/A";
    }

    NODE_TYPE_NAME("ERROR")
    NODE_TYPE_GETTER(ERROR)
};

struct Identifier final : Node {
    std::string value;

    Identifier() {
    }

    Identifier(std::string value) {
        this->value = value;
    }

    NODE_TYPE_NAME("Identifier")
    NODE_TYPE_GETTER(IDENTIFIER)

    virtual void pretty_print(PrettyStream &out) {
        out << Color::YELLOW << value << Color::NONE;
    }
};

constexpr auto identifier_any = "Any";

} // namespace ast
#endif
