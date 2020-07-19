#ifndef APP_HPP
#define APP_HPP

#include "gameview.hpp"
#include "menu.hpp"
#include "statusbar.hpp"

class App {
public:
    App();
    ~App();
    
    static void loop();
    static void quit();    
    
    static GameView* gameView;
    static Game* game;
    static Menu* menu;
    
    static inline Statusbar* const statusbar() {return _statusbar;};
private:
    static bool _loop;
    static Statusbar* _statusbar;
};

#endif // APP_HPP
