#include <iostream>

#include "nfa/passes/print_nfa.hpp"
#include "string.hpp"

using namespace std;

namespace nfa {

void Printer::visit(sptr<State> s) {
    auto indent = "    ";
    cout << "State " << s->state_id << ":" << endl;
    if (s->action.complete_node) {
        cout << indent << "Completes node " << s->action.node << endl;
    }
    if (s->action.new_node) {
        cout << indent << "Creates new node with precedence "
             << (int)s->action.precedence << endl;
    }

    for (unsigned long i = 0; i < s->next.size(); i++) {
        Transition &t = s->next.get(i);
        cout << indent << escape(t.req.character) << "(p>"
             << (int)t.req.precedence << ",n>" << (int)t.req.nodes << ")"
             << " → " << t.state->state_id << endl;
    }
    cout << endl;
}

} // namespace nfa
