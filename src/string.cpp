#include <sstream>

#include "string.hpp"

using namespace std;

string escape(char c) {
    switch (c) {
    case '\n':
        return "\\n";
    case '\t':
        return "\\t";
    case '\0':
        return "\\0";
    }
    stringstream out;
    out << c;
    return out.str();
}

string escape(string s) {
    stringstream out;

    for (char c : s) {
        out << escape(c);
    }

    return out.str();
}
