#include "app.hpp"
#include "colorscheme.hpp"
#include "menu.hpp"

const std::string Menu::options[]  = {
        "New game",
//         "Restart game",
//         "Help",
        "Quit"
    };

Menu::Menu (int height, int width, int y0, int x0)
    : Widget(height, width, y0, x0) {
        calculateLayout();
        wbkgd(window(), COLOR_PAIR(ColorScheme::Menu));
        draw();
}

void Menu::draw() {
    wbkgd(window(), COLOR_PAIR(ColorScheme::Menu));
    wmove(window(),0,0);
    int count = sizeof(options) / sizeof(std::string);
    int cursorY = 0, cursorX = 0;
    wmove(window(), 0, 0);
    for(int i = 0;;) {
        waddch(window(), options[i][0] | A_UNDERLINE);
        waddstr(window(), options[i].substr(1).c_str());
        cursorX += options[i].length() + separatingSpace;
        if(++i == count) break;
        else wmove(window(), cursorY, cursorX);
    }
    wrefresh(window());
}

void Menu::calculateLayout() {
    int count = sizeof(options) / sizeof(std::string);
    int len = 0;
    for(auto& s: options) len += s.length();
    separatingSpace = (width() - len) / (count - 1);
}


bool Menu::keyEvent (int ch){
    switch(ch) {
        case 'n':
        case 'N':
            App::newGame();
            return true;
        case 'q':
        case 'Q':
            App::quit();
            return true;
        default:
         return false;
    }
}


