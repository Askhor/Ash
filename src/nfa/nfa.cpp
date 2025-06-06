#include <algorithm>

#include "nfa/nfa.hpp"
#include "nfa/passes/print_nfa.hpp"

using namespace std;
using namespace nfa;

void Table::optimise() {
    if (sorted)
        return;

    sort(transitions.begin(), transitions.end());

    sorted = true;
}

void Table::add(Transition t) {
    transitions.emplace_back(t);
    sorted = false;
}

Transition &Table::get(unsigned long index) {
    optimise();
    return transitions[index];
}

unsigned long Table::find(Req r) {
    optimise();

    unsigned long lower = 0;
    unsigned long upper = transitions.size();

    // while (true) {
    //      int middle = (lower + upper) / 2;
    //      if(stuff[middle] == el) return middle;
    //      if (lower == upper) return -1;
    //      if(stuff[middle] < el) {
    //          lower = middle;
    //          continue
    //      }
    //      upper = middle;
    // }

    while (true) {
        unsigned long middle = (lower + upper) / 2;

        Transition left = transitions[middle];
        Transition right = transitions[middle + 1];

        if (left.req.character < r.character &&
            r.character == right.req.character) {
            return middle + 1;
        }

        if (lower == upper) {
            return -1;
        }

        if (r.character < right.req.character) {
            upper = middle;
            continue;
        }

        lower = middle;
    }
}

unsigned long Table::size() {
    return transitions.size();
}
