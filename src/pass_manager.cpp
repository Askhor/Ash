#include "pass_manager.hpp"
#include "ast/passes/merge_regexes.hpp"
#include "ts2ast.hpp"
#include "tsparsing.hpp"

void run_passes(std::string src, TSTree *tree, int dump_level) {
#define DUMP_HERE(code)                                                        \
    if (--dump_level == 0) {                                                   \
        code;                                                                  \
        return;                                                                \
    }

#define DUMP_AST                                                               \
    ast::PrettyStream out(&std::cout);                                         \
    file->pretty_print(out);                                                   \
    out.new_line();

    DUMP_HERE(ts_debug_print(src, tree))

    sptr<ast::File> file = ast::read_file(src, ts_tree_root_node(tree));

    DUMP_HERE(DUMP_AST)

    merge_regexes(file);

    DUMP_HERE(DUMP_AST)

#undef DUMP_HERE
#undef DUMP_AST
}
