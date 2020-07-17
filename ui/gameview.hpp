#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <curses.h>

#include "core/game.hpp"
#include "ui/widget.hpp"

class GameView : public Widget {
public:
    GameView(int height, int width, int y0, int x0);
    
    inline Game* game() const {return _game;}
    void setGame(Game* );
        
    int maxGameHeight() const;
    int maxGameWidth() const;
    
    virtual void draw() override;
    
    constexpr static int SQUARE_WIDTH = 2;
    constexpr static const char* SURROUNDING_STRINGS[9]  = {"  ", "1 ","2 ","3 ","4 ","5 ","6 ","7 ","8 "};
    
    
    bool mouseEvent( MEVENT*);
private:
    Game* _game;
};

#endif // GAMEVIEW_HPP
