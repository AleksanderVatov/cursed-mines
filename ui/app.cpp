#include <clocale>

#include <curses.h>

#include "colorscheme.hpp"
#include "app.hpp"

bool App::_loop;

App::App() {
    //Set up curses
    std::setlocale(LC_ALL, "");
    initscr(); // Initialize screen
    cbreak(); // Read characters one at a time
    noecho(); // Do not write input characters to screen
    nodelay(stdscr, TRUE); // Make getch return ERR in the absence of input rather than waiting
    keypad(stdscr, TRUE); // Allows receiving special keys directly (rather than interpreting escape codes)
    curs_set(0); // Hide cursor
    
    ColorScheme::initColors();
    
    mousemask(ALL_MOUSE_EVENTS, nullptr);
    refresh(); // Apparently a refresh is needed after initscr.
        
    gameView = new GameView(LINES - 1, COLS, 1, 0);
    game = new Game(gameView->maxGameHeight(), gameView->maxGameWidth());
    gameView->setGame(game);
    gameView->draw();
    
    Widget::processInput();
}

App::~App() {
    delete gameView;
    delete game;
    
    endwin();
}

void App::loop() {
    _loop = true;
    while(_loop) Widget::processInput(false);
}

void App::quit() {
    _loop = false;
}



