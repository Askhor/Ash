#include <string>
#include <tree_sitter/api.h>

void expect(std::string src, TSNode, std::string expected);
std::string ts_node_value(std::string src, TSNode);
