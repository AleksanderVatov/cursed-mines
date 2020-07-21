#include <clocale>

#include <curses.h>

#include "colorscheme.hpp"
#include "app.hpp"
#include <curses.h>

Game     * App::game;
GameView * App::gameView;
Menu     * App::menu;
Statusbar* App::_statusbar = nullptr;

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
    
    int h, w;
    getmaxyx(stdscr, h, w);
    
    
    menu = new Menu(1, w, 1, 0);
    menu->draw();
    
    gameView = new GameView(h - 3, w, 2, 0);
    game = new Game(gameView->maxGameHeight(), gameView->maxGameWidth());
    gameView->setGame(game);
    gameView->draw();
    
    
    _statusbar = new Statusbar(1, w, 0, 0);
    _statusbar->setDefaults(0.15*game->height()*game->width(), 0);
    _statusbar->setText("Cursed Minesweeper");
}

App::~App() {
    delete gameView;
    delete game;
    
    endwin();
}

void App::run() {
    Widget::eventLoop();
}

void App::quit() {
    Widget::quitEventLoop();
}

void App::newGame() {
    game->clear();
    gameView->draw();
    statusbar()->setText("Cursed Minesweeper");
    statusbar()->update();
    menu->draw();
    refresh();
}

