#include <algorithm>

#include "widget.hpp"

std::vector<Widget*> Widget::_widgets;

Widget::Widget(int height, int width, int y0, int x0 ) {
    _height = height;
    _width = width;
    _y0 = y0;
    _x0 = x0;
    
    _win = newwin(height, width, y0, x0);
    _widgets.push_back(this);
}

Widget::~Widget() {
    delwin(_win);
    _widgets.pop_back();
}


bool Widget::mouseEvent ( MEVENT* ) {
    return false;
}

bool Widget::keyEvent (int ch) {
    return false;
}

void Widget::processInput(bool loop) {
        MEVENT mouseEvent;
    do {
        int ch;
        switch(ch = getch()) {
            case KEY_MOUSE:
//                     std::cout << '\a' << std::flush;
//                     mvaddstr(0, 0, "Received mouse event");
//                     refresh();
//                 if(getmouse(&mouseEvent) == OK) {
                    getmouse(&mouseEvent);
                    for(auto it = _widgets.rbegin(); it != _widgets.rend(); ++it) {
                        Widget * w = *it;
                        if(mouseEvent.y - w->y0() < w->height() && mouseEvent.x - w->x0() < w->width())
                            w->mouseEvent(&mouseEvent);
                    }
                    break;
//                 }
            case ERR:
                break;
            default:
                // Pass to widgets
                for(auto it = _widgets.rbegin(); it != _widgets.rend(); ++it) {
                        Widget * w = *it;
                        if((*it)->keyEvent(ch))
                            break;
                }
        }
    } while(loop);
}
