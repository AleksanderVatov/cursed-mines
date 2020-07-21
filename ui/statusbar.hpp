#ifndef STATUSBAR_HPP
#define STATUSBAR_HPP

#include <string>

#include "widget.hpp"

class Statusbar : public Widget {
public:
    Statusbar(int height, int width, int y0, int x0, unsigned mines = 0, unsigned flags = 0);
    
    std::string const & text() const;
    void setText(std::string const& newText);
    
    void setDefaults(unsigned mines, unsigned flags = 0);
    
    virtual void draw() override;
    void update();
    
protected:
    void calculateLayout();
    
private:
    std::string _text;
    unsigned short _availableSpace, _textAreaStart, _cornerWidth;
    unsigned short _mines = 0, _flags = 0, _defaultMines, _defaultFlags;
};

#endif //STATUSBAR_HPP
