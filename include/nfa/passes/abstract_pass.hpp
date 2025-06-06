#ifndef ABSTRACT_PASS_HPP
#define ABSTRACT_PASS_HPP

#include <stdexcept>

#include "nfa/nfa.hpp"

namespace nfa {

struct Visitor {
    virtual void visit(sptr<State> s) {
        throw std::runtime_error("Undefined visit method");
    }
};

void visit_all(Visitor &visitor, sptr<nfa::State> start);

} // namespace nfa

#endif
