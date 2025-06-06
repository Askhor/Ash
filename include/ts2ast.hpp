#include "ast/ast.hpp"
#include <tree_sitter/api.h>

namespace ast {

sptr<ast::File> read_file(std::string, TSNode);
sptr<ast::TokenDefinition> read_token_definition(std::string, TSNode);
sptr<ast::AbstractNodeDefinition> read_abstract_node_definition(std::string,
                                                                TSNode);
sptr<ast::NodeDefinition> read_node_definition(std::string, TSNode);
sptr<ast::Identifier> read_identifier(std::string, TSNode);
sptr<ast::Regex> read_regex(std::string, TSNode);

sptr<ast::Field> read_field(std::string, TSNode);
sptr<ast::Field> read_regex_field(std::string, TSNode);
sptr<ast::Field> read_node_field(std::string, TSNode);

} // namespace ast
