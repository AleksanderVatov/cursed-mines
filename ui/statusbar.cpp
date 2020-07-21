#include <string>

#include <curses.h>

#include "app.hpp"
#include "colorscheme.hpp"
#include "statusbar.hpp"

Statusbar::Statusbar(int height, int width, int y0, int x0)
    : Widget(height, width, y0, x0 ){
        wbkgd(window(), COLOR_PAIR(ColorScheme::Statusbar));
        calculateLayout();
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
    _availableSpace = width() - 6;
    _textAreaStart = 3;
}


void Statusbar::draw() {
    wclear(window());
    
    wmove(window(), 0, 0);
    waddstr(window(), ("🚩" + std::to_string(_flags)).c_str());
    
    wmove(window(), 0, _textAreaStart + (_availableSpace - _text.length()) / 2);
    waddstr(window(), _text.c_str());
    
    wmove(window(), 0, width() - 3);
    waddstr(window(), (std::to_string(_mines) + "💥").c_str());
    
    wrefresh(window());
}

void Statusbar::update() {
    int flags = App::game->numberOfFlags(), mines = App::game->numberOfMines();
    if(_flags != flags || _mines != mines) {
        _flags = flags;
        _mines = mines;
        draw();
    }
}

