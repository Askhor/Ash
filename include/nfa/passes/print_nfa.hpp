#ifndef PRINT_NFA_HPP
#define PRINT_NFA_HPP

#include "nfa/passes/abstract_pass.hpp"

namespace nfa {
struct Printer final : Visitor {
    virtual void visit(sptr<State> s);
};
} // namespace nfa

#endif
