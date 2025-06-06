#ifndef TCOLOR_HPP
#define TCOLOR_HPP

#include <iostream>
#include <string>

#define ANSI_RGB(r, g, b)                                                      \
    "\e[38;2;" + std::string(#r) + ";" + std::string(#g) + ";" +               \
        std::string(#b) + "m"

// clang-format off
#define COLORS_LIST(code)                                                      \
    code(NONE, "\e[0m")                                                        \
    code(RED, ANSI_RGB(255, 0, 0))                                             \
    code(DARK_RED, ANSI_RGB(150, 0, 0))                                        \
    code(DARK_GREEN, ANSI_RGB(0, 150, 0))                                      \
    code(YELLOW, ANSI_RGB(255, 255, 0))                                        \
    code(ORANGE, ANSI_RGB(255, 150, 0))
// clang-format on

#define LIST_COLOR(color, ignored) color,

enum class Color { COLORS_LIST(LIST_COLOR) };

#undef LIST_COLOR

std::string get_color_string(Color c);
std::ostream &operator<<(std::ostream &out, Color c);
#endif
