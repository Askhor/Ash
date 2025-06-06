#ifndef NFA_HPP
#define NFA_HPP

#include <vector>

#include "nfa/constants.hpp"
#include "shared_pointers.hpp"

namespace nfa {

struct State;
struct Table;
struct Req;
struct Transition;
struct Action;

struct Req {
    char character;
    uint8_t precedence = 0;
    uint8_t nodes = 0;

    bool operator<(Req other) {
        return character < other.character;
    }
};

struct Action {
    bool complete_node = false;
    node_id node;
    bool new_node = false;
    uint8_t precedence;
};

struct Table {
  private:
    bool sorted = false;
    std::vector<Transition> transitions;

  public:
    void add(Transition t);
    Transition &get(unsigned long index);
    unsigned long find(Req r);
    void optimise();
    unsigned long size();
};

struct State {
    int state_id = -1;
    Table next;
    Action action;
    int visit_id = 0;
};

struct Transition {
    Req req;
    sptr<State> state;

    bool operator<(Transition other) {
        return req < other.req;
    }
};

} // namespace nfa

#endif
