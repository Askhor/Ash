#include "tcolor.hpp"

std::string get_color_string(Color c) {
#define DEFINE_COLOR(color, value)                                             \
    case Color::color:                                                         \
        return value;

    switch (c) {
        COLORS_LIST(DEFINE_COLOR);
    default:
        throw std::runtime_error("Not all color values have been defined");
    }

#undef DEFINE_COLOR
}

std::ostream &operator<<(std::ostream &out, Color c) {
    out << get_color_string(c);
    return out;
}
