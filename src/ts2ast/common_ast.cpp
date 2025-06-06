#include "ts2ast.hpp"
#include "ts2ast_helper.hpp"

int min(int a, int b) {
    return a > b ? b : a;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void expect(std::string src, TSNode node, std::string expected) {
    std::string found = ts_node_type(node);
    if (found == expected)
        return;

    int node_start = ts_node_start_byte(node);
    int context = 20;
    int start = max(0, node_start - context);
    int end = min(src.size() - 1, node_start + context);

    throw std::runtime_error(
        "Expected " + expected + " but found " + found + ". The context is \n" +
        src.substr(start, node_start - start) +
        "\nTHIS IS WHERE THERE SHOULD HAVE BEEN THE " + expected + "\n" +
        src.substr(node_start, end - node_start));
}

std::string ts_node_value(std::string src, TSNode node) {
    int start = ts_node_start_byte(node);
    int len = ts_node_end_byte(node) - start;
    return src.substr(start, len);
}

sptr<ast::Identifier> ast::read_identifier(std::string src, TSNode node) {
    expect(src, node, "identifier");
    ast::Identifier id;

    int start = ts_node_start_byte(node);
    int end = ts_node_end_byte(node);
    id.value = src.substr(start, end - start);

    return std::make_shared<ast::Identifier>(id);
}
sptr<ast::Regex> ast::read_regex(std::string src, TSNode node) {
    expect(src, node, "regular_expr");
    ast::Regex re;

    int start = ts_node_start_byte(node) + 1;
    int end = ts_node_end_byte(node);

    re.value = src.substr(start, end - start);

    return std::make_shared<ast::Regex>(re);
}
