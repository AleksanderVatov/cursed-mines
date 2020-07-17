#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <vector>

#include <curses.h>

class Widget {
public:
    Widget(int height, int width, int y0, int x0);
    virtual ~Widget();
    
    inline int height() const {return _height;}
    inline int width() const {return _width;}
    inline int y0() const {return _y0;}
    inline int x0() const {return _x0;}
    
    static void processInput(bool loop = true);
protected:
    inline WINDOW * window() {return _win;};
    virtual bool mouseEvent(MEVENT *);
    virtual bool keyEvent(int ch);
    
    virtual void draw() = 0;
    
private:
    static std::vector<Widget*> _widgets;
    WINDOW * _win;
    int _height, _width, _y0, _x0;
    
};
#endif // WIDGET_HPP
