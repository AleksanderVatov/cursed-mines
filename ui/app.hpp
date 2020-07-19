#ifndef APP_HPP
#define APP_HPP

#include "gameview.hpp"
#include "menu.hpp"

class App {
public:
    App();
    ~App();
    
    static void loop();
    static void quit();    
    
    static GameView* gameView;
    static Game* game;
    static Menu* menu;
private:
    static bool _loop;
};

#endif // APP_HPP
