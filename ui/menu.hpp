#ifndef MENU_HPP
#define MENU_HPP

#include "widget.hpp"

class Menu : public Widget {
public:
    Menu(int height, int width, int y0, int x0);
    
    virtual void draw() override;
    
protected:
    bool keyEvent (int ch) override;
};
#endif // MENU_HPP
