#include <string>

#include <curses.h>

#include "app.hpp"
#include "colorscheme.hpp"
#include "statusbar.hpp"

Statusbar::Statusbar(int height, int width, int y0, int x0, unsigned mines, unsigned flags)
    : Widget(height, width, y0, x0 ){
        setDefaults(mines, flags);
        wbkgd(window(), COLOR_PAIR(ColorScheme::Statusbar));
        update();
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

void Statusbar::setDefaults(unsigned int mines, unsigned int flags) {
    _defaultMines = mines;
    _defaultFlags = flags;
    update();
}


void Statusbar::calculateLayout() {
    int mines = _mines, digits = 1;
    while(mines /= 10) ++digits;
    
    _cornerWidth = digits + 2;
    _textAreaStart = digits + 2;
    _availableSpace = width() - 2*_cornerWidth;
}


void Statusbar::draw() {
    wclear(window());
    
    wmove(window(), 0, 0);
    waddstr(window(), ("🚩" + std::to_string(_flags)).c_str());
    
    wmove(window(), 0, _textAreaStart + (_availableSpace - _text.length()) / 2);
    waddstr(window(), _text.c_str());
    
    wmove(window(), 0, width() - _cornerWidth);
    waddstr(window(), (std::to_string(_mines) + "💥").c_str());
    
    wrefresh(window());
}

void Statusbar::update() {
    int flags, mines;
    if(App::game->state() == Game::NotStarted) {
        flags = _defaultFlags;
        mines = _defaultMines;
    } else {
        flags = App::game->numberOfFlags();
        mines = App::game->numberOfMines();
    }
    
    if(_flags != flags || _mines != mines) {
        _flags = flags;
        _mines = mines;
        calculateLayout();
        draw();
    }
}

