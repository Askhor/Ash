#include "ts2ast.hpp"
#include "ts2ast_helper.hpp"

sptr<ast::File> ast::read_file(std::string src, TSNode node) {
    expect(src, node, "source_file");

    ast::File file;

    int child_count = ts_node_child_count(node);
    for (int i = 0; i < child_count; i++) {

        TSNode child = ts_node_child(node, i);
        std::string type = ts_node_type(child);

        sptr<ast::Definition> def;

        if (type == "token_definition") {
            def = ast::read_token_definition(src, child);
        } else if (type == "node_definition") {
            def = ast::read_node_definition(src, child);
        } else if (type == "abstract_node_definition") {
            def = ast::read_abstract_node_definition(src, child);
        } else {
            throw std::runtime_error("Unknown top-level node \"" + type + "\"");
        }

        file.definitions.emplace_back(def);

        /*int start = ts_node_start_byte(child);
                int len = ts_node_end_byte(child) - start;
                std::cout << src.substr(start, len) << std::endl;*/
    }

    file.definitions.emplace_back(create_any());

    return std::make_shared<ast::File>(file);
}
