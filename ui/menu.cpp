#include "app.hpp"
#include "menu.hpp"

Menu::Menu (int height, int width, int y0, int x0): Widget(height, width, y0, x0) {
    
}

void Menu::draw() {
}

bool Menu::keyEvent (int ch){
    switch(ch) {
        case 'n':
        case 'N':
            App::game->reset();
            clear();
            refresh(); // The screen needs to be refreshed after it's cleared and before drawing
            App::gameView->draw();
            return false;
        case 'q':
        case 'Q':
            App::quit();
            return true;
        default:
         return false;
    }
}
