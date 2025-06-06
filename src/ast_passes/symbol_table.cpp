#include "ast/passes/symbol_table.hpp"

using namespace std;
using namespace ast;

void cst_def(sptr<File> file, sptr<Definition> def) {
    file->symbol_table[def->name->value] = def;
}

void ast::create_symbol_table(sptr<File> file) {
    for (sptr<Definition> def : file->definitions) {
        cst_def(file, def);
    }
}
