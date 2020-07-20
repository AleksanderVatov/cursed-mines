#ifndef MENU_HPP
#define MENU_HPP

#include "widget.hpp"

class Menu : public Widget {
public:
    Menu(int height, int width, int y0, int x0);
    
    virtual void draw() override;
    
protected:
    void calculateLayout();
    bool keyEvent (int ch) override;
    
private:
    const static std::string options[];
    unsigned short separatingSpace;
};
#endif // MENU_HPP
