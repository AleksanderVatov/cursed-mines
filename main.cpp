#include <curses.h>

#include <clocale>
#include <iostream>

#include "core/game.hpp"
#include "ui/gameview.hpp"


// const char* surrounding[9] = {"  ", "1.","2.","3.","4.","5.","6.","7.","8."};

std::size_t field_height = 20, field_width = 20;

enum GameState {
    NotStarted,
    Running,
    Lost,
    Won
};

int main(int argc, char **argv) {
    Game game(field_height, field_width);
    GameState state = NotStarted;
    
//     field.plantMines(10, 0, 0);
//     field.reveal(0, 0);
//     for(Square & sq: field) sq.setState(Square::Open);
    
    //Set up curses
    std::setlocale(LC_ALL, "");
    initscr(); // Initialize screen
    cbreak(); // Read characters one at a time
    noecho(); // Do not write input characters to screen
    nodelay(stdscr, TRUE); // Make getch return ERR in the absence of input rather than waiting
    curs_set(0); // Hide cursor
    start_color(); // Initialize colors
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_BLACK, COLOR_RED);
    
    mousemask(ALL_MOUSE_EVENTS, nullptr);
    
//     mousemask(BUTTON1_RELEASED | BUTTON1_DOUBLE_CLICKED | BUTTON2_CLICKED, nullptr);

    refresh(); // Apparently a refresh is needed after initscr.
        
    int win_h = field_height, win_w = 2*field_width, win_y0 = (LINES - win_h)/2, win_x0 = (COLS - win_w) / 2;
//     wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
    GameView *win = new GameView(win_h, win_w, win_y0, win_x0);
    win->setGame(&game);
    win->draw();
    MEVENT mouseEvent;
    for(int c = wgetch(win->_win); ; c = wgetch(win->_win)) {
        switch(c) {
            case KEY_MOUSE: {
//                     std::cout << '\a' << std::flush;
//                     mvaddstr(0, 0, "Received mouse event");
//                     refresh();
//                 if(getmouse(&mouseEvent) == OK) {
                    getmouse(&mouseEvent);
                    int y = mouseEvent.y - win_y0, x = (mouseEvent.x - win_x0)/2;
                    if(y < 0 || y >= field_height || x < 0 || x > field_width) break;
                    if(mouseEvent.bstate & (BUTTON1_CLICKED | BUTTON1_PRESSED)) {
//                         mvprintw(0, 0, "Received click at %i,%i", y, x);
//                         refresh();
                        switch(state) {
                            case NotStarted:
                                game.plantMines(0.15*(field_height*field_width), y, x);
                                game.reveal(y, x);
                                state = Running;
                                win->draw();
                                break;
                            case Running:
                                if(game(y, x).state() == Square::Open) break; // Avoid redrawing unnecessarily
                                if(game.reveal(y, x)) {
                                    mvprintw(0, 0, "Game lost!");
                                    for(Square & sq: game) sq.setState(Square::Open);
                                }
                                win->draw();
                                break;
                            case Lost:
                                break;
                        }
                        game.reveal(y, x);
                        win->draw();
//                         wrefresh(win);
                        refresh();
                    }
                    else if(mouseEvent.bstate & (BUTTON3_CLICKED | BUTTON3_PRESSED)) {
//                         mvprintw(0, 0, "Received right click at %i,%i", y, x);
//                         refresh();
                        game.toggleFlag(y, x);
                        win->draw();
                    }
                    else if(mouseEvent.bstate & BUTTON1_DOUBLE_CLICKED) {
                        if(game.revealUnflaggedNeighbors(y, x)) {
                            state = Lost;
                            mvprintw(0, 0, "Game lost!");
                        }
                        win->draw();
                    }
//                 }
                break;
            }
            case 'n':
            case 'N':
                game.reset();
                state = NotStarted;
                clear();
                refresh(); // The screen needs to be refreshed after it's cleared and before drawing
                win->draw();
                break;
            case 'q':
            case 'Q':
                endwin();
                return 0;
            case ERR:
                break;
            default:
//                 std::cout << '\a';
//                 mvaddstr(0, 0, "Received unknown key");
//                 refresh();
                break;
        }
    }
}
