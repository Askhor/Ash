#include <stack>

#include "nfa/passes/abstract_pass.hpp"

using namespace std;
using namespace nfa;

int visit_id = 0;

void nfa::visit_all(Visitor &visitor, sptr<State> start) {
    stack<sptr<State>> to_visit;
    to_visit.push(start);

    int this_visit_id = ++visit_id;

    while (to_visit.size() > 0) {
        sptr<State> s = to_visit.top();
        to_visit.pop();

        if (s->visit_id == this_visit_id)
            continue;

        s->visit_id = this_visit_id;

        visitor.visit(s);

        for (unsigned long i = 0; i < s->next.size(); i++) {
            to_visit.push(s->next.get(i).state);
        }
    }
}
