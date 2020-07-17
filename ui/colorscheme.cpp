#include <curses.h>

#include "colorscheme.hpp"

void ColorScheme::initColors() {
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_BLACK, COLOR_RED);
    init_pair(StatusBar, COLOR_BLACK, COLOR_YELLOW);
    init_pair(Menu, COLOR_BLACK, COLOR_YELLOW);
}
