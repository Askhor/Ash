#ifndef RESOLVE_HPP
#define RESOLVE_HPP

#include "ast/ast.hpp"

namespace ast {
void resolve_symbols(sptr<File> file);
}

#endif
