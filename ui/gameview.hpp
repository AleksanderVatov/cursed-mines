#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <curses.h>

#include "core/game.hpp"
#include "ui/widget.hpp"

class GameView : public Widget {
public:
    constexpr static int SQUARE_WIDTH = 2;
    constexpr static const char* SURROUNDING_STRINGS[9]  = {"  ", "1 ","2 ","3 ","4 ","5 ","6 ","7 ","8 "};
    
    GameView(int height, int width, int y0, int x0);
    
    inline Game* game() const {return _game;}
    void setGame(Game* );
        
    int maxGameHeight() const;
    int maxGameWidth() const;
    
    virtual void draw() override;
    bool mouseEvent(MEVENT*) override;
    
protected:
    void calculateLayout();
    
private:
    Game* _game;
    int _maxRows, _maxCols;
    int field_y0, field_x0;
};

#endif // GAMEVIEW_HPP
