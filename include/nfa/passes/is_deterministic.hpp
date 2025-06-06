#ifndef IS_DETERMINISTIC_HPP
#define IS_DETERMINISTIC_HPP

#include "nfa/passes/abstract_pass.hpp"

namespace nfa {

struct IsDeterministic : Visitor {
    bool result = true;
    virtual void visit(sptr<State> s);
};

} // namespace nfa

#endif
