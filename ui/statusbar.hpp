#ifndef STATUSBAR_HPP
#define STATUSBAR_HPP

#include <string>

#include "widget.hpp"

class Statusbar : public Widget {
public:
    Statusbar(int height, int width, int y0, int x0);
    
    std::string const & text() const;
    void setText(std::string const& newText);
    
    virtual void draw() override;
protected:
    
    void calculateLayout();
    
private:
    std::string _text;
    unsigned short _availableSpace;
};

#endif //STATUSBAR_HPP
