#include "colorscheme.hpp"
#include "statusbar.hpp"

#include "curses.h"

Statusbar::Statusbar(int height, int width, int y0, int x0)
    : Widget(height, width, y0, x0 ){
        wbkgd(window(), COLOR_PAIR(ColorScheme::Statusbar));
        draw();
}

const std::string & Statusbar::text() const {
    return _text;
}

void Statusbar::setText(const std::string& newText) {
    _text = newText.substr(0, _availableSpace);
    draw();
}

void Statusbar::calculateLayout() {
    _availableSpace = width();
}


void Statusbar::draw() {
//     wattron(window(), COLOR_PAIR(ColorScheme::Statusbar));
    wclear(window());
    wmove(window(), 0, (width() - _text.length()) / 2);
    waddstr(window(), _text.c_str());
//     wattroff(window(), COLOR_PAIR(ColorScheme::Statusbar));
    wrefresh(window());
}
