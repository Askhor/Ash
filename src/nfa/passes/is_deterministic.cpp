#include "nfa/passes/is_deterministic.hpp"

void nfa::IsDeterministic::visit(sptr<State> s) {
    int c = -1;

    for (unsigned long i = 0; i < s->next.size(); i++) {
        int other_char = (int)s->next.get(i).req.character;

        if (other_char == c)
            result = false;
        c = other_char;
    }
}
