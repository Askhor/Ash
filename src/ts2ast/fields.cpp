#include "ts2ast.hpp"
#include "ts2ast_helper.hpp"
#include "tsparsing.hpp"

sptr<ast::Field> ast::read_field(std::string src, TSNode node) {
    std::string type = ts_node_type(node);
    if (type == "regular_expr") {
        return ast::read_regex_field(src, node);
    } else if (type == "node_field") {
        return ast::read_node_field(src, node);
    } else {
        throw std::runtime_error("Unknown ast type for field: \"" + type +
                                 "\"");
    }
}
sptr<ast::Field> ast::read_regex_field(std::string src, TSNode node) {
    ast::RegexField field;

    field.regex = read_regex(src, node);

    return std::make_shared<ast::RegexField>(field);
}

ast::NodeFieldModifier read_node_field_modifier(std::string src, TSNode node) {
    expect(src, node, "field_modifier");
    if (ts_node_named_child_count(node) == 0) {
        throw std::runtime_error(
            "Field modifier must exist if it does exist (?)");
    }
    TSNode child = ts_node_named_child(node, 0);
    std::string type = ts_node_type(child);

    if (type == "array_modifier")
        return ast::NodeFieldModifier::ARRAY;
    else if (type == "optional_modifier")
        return ast::NodeFieldModifier::OPTIONAL;
    else
        throw std::runtime_error("Unknown field modifier: " + type);
}

sptr<ast::Field> ast::read_node_field(std::string src, TSNode node) {
    expect(src, node, "node_field");
    ast::NodeField field;

#define CHILD ts_node_named_child(node, child_index)
#define CHILD_NEXT ts_node_named_child(node, child_index++)

    int child_count = ts_node_named_child_count(node);
    int child_index = 0;

    if (child_index >= child_count)
        throw std::runtime_error(
            "A node field needs at least an identifier an a type");

    if (ts_node_type(CHILD) == (std::string) "field_modifier") {
        field.modifier = read_node_field_modifier(src, CHILD_NEXT);
    } else {
        field.modifier = NodeFieldModifier::NONE;
    }

    if (child_index >= child_count)
        throw std::runtime_error(
            "A node field needs at least an identifier an a type");

    field.name = read_identifier(src, CHILD_NEXT);

    if (child_index >= child_count)
        throw std::runtime_error("A node field needs a type");

    field.type = read_identifier(src, CHILD_NEXT);

    return std::make_shared<ast::NodeField>(field);

#undef CHILD
}
