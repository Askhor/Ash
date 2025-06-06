#include "ast/passes/resolve.hpp"

using namespace std;
using namespace ast;

#define DEFINE_FUN(class, name)                                                \
    void rs_##name(sptr<File> file, sptr<class> name)

DEFINE_FUN(Identifier, id) {
    string name = id->value;

    if (file->symbol_table[name] == nullptr) {
        cout << Color::DARK_RED << "No definition for '" << name << "'"
             << Color::NONE << endl;
        file->error = true;
        return;
    }
    id->ref = file->symbol_table[name];
}

DEFINE_FUN(Definition, def) {
    if (def->name == nullptr)
        throw runtime_error("Name is null");
    if (def->supertype == nullptr)
        throw runtime_error("Supertype is null");

    rs_id(file, def->name);
    rs_id(file, def->supertype);
}

DEFINE_FUN(TokenDefinition, tok) {
    rs_def(file, CAST(Definition)(tok));
}

DEFINE_FUN(NodeDefinition, node) {
    rs_def(file, CAST(Definition)(node));
}

DEFINE_FUN(AbstractNodeDefinition, abnode) {
    rs_def(file, CAST(Definition)(abnode));
}

#undef DEFINE_FUN

void recurse(sptr<File> file, sptr<Node> node) {
#define CASE(type, class, name)                                                \
    case Type::type:                                                           \
        rs_##name(file, CAST(class)(node));                                    \
        break;

    switch (node->get_type()) {
        CASE(TOKEN, TokenDefinition, tok)
        CASE(NODE, NodeDefinition, node)
        CASE(ABSTRACT_NODE, AbstractNodeDefinition, abnode)

    default:
        throw runtime_error(
            "Resolve Symbols cannot be called on nodes of type " +
            node->type_name());
    }

#undef CASE
}

void ast::resolve_symbols(sptr<File> file) {
    for (sptr<Definition> def : file->definitions) {
        recurse(file, def);
    }

    if (file->error) {
        throw runtime_error("Not all identifiers could be resolved");
    }
}
