#include "ts2ast.hpp"
#include "ts2ast_helper.hpp"

#define read_definition_start(type, ts_type, variable_remover)                 \
    expect(src, node, ts_type);                                                \
    type def;                                                                  \
                                                                               \
    int child_index = 0;                                                       \
                                                                               \
    read_definition_header(def, child_index, src, node);

#define define_child_count int child_count = ts_node_named_child_count(node);

sptr<ast::Identifier> read_type_declaration(std::string src, TSNode node) {
    expect(src, node, "type_declaration");
    return ast::read_identifier(src, ts_node_named_child(node, 0));
}

void read_definition_header(ast::Definition &into, int &child_index,
                            std::string src, TSNode node) {
    define_child_count

        if (child_index >= child_count) throw std::runtime_error(
            "Could not read definition: Identifier missing");

    into.name =
        ast::read_identifier(src, ts_node_named_child(node, child_index++));

    if (child_index < child_count) {
        TSNode child = ts_node_named_child(node, child_index);
        if (ts_node_type(child) == (std::string) "type_declaration") {
            into.supertype = read_type_declaration(src, child);
            child_index++;
        }
    } else {
        into.supertype = std::make_shared<ast::Identifier>(ast::identifier_any);
    }
}

sptr<ast::TokenDefinition> ast::read_token_definition(std::string src,
                                                      TSNode node) {

    read_definition_start(ast::TokenDefinition, "token_definition", );
    define_child_count

        if (child_index >= child_count) {
        throw std::runtime_error("Token definition is missing token");
    }

    TSNode regex = ts_node_named_child(node, child_index);
    def.regex = ast::read_regex(src, regex);

    return std::make_shared<ast::TokenDefinition>(def);
}
sptr<ast::AbstractNodeDefinition>
ast::read_abstract_node_definition(std::string src, TSNode node) {
    read_definition_start(ast::AbstractNodeDefinition,
                          "abstract_node_definition", if (false));
    return std::make_shared<ast::AbstractNodeDefinition>(def);
}
sptr<ast::NodeDefinition> ast::read_node_definition(std::string src,
                                                    TSNode node) {
    read_definition_start(ast::NodeDefinition, "node_definition", );
    define_child_count

        for (; child_index < child_count; child_index++) {
        TSNode field = ts_node_named_child(node, child_index);
        def.fields.emplace_back(ast::read_field(src, field));
    }

    return std::make_shared<ast::NodeDefinition>(def);
}

#undef read_definition_start
#undef define_child_count
