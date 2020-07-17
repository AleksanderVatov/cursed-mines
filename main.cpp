#include <curses.h>

#include <clocale>
#include <iostream>

#include "minefield.hpp"

const char* surrounding[9] = {"  ", "1 ","2 ","3 ","4 ","5 ","6 ","7 ","8 "};
// const char* surrounding[9] = {"  ", "1.","2.","3.","4.","5.","6.","7.","8."};

enum GameState {
    NotStarted,
    Running,
    Over
};

void drawField(WINDOW* win, Minefield const& field) {
    wmove(win, 0, 0);
    for(Square sq: field) {
        switch(sq.state()) {
            case Square::Open:
                if(sq.isMined()) 
                    waddstr(win, "💥"); //Too wide
                else {
                    auto surroundingMines = sq.surroundingMines();
                    wattron(win, COLOR_PAIR(surroundingMines));
                    waddstr(win, surrounding[surroundingMines]);
                    wattroff(win, COLOR_PAIR(surroundingMines));
                }
                break;
            case Square::Flagged:
                waddstr(win, "🚩");
                break;
            case Square::QuestionMark:
                waddstr(win, "❔");
                break;
            case Square::Closed:
            default:
                waddstr(win, "⬛");
                break;
        }
//         wattron(win,COLOR_PAIR(0));
    }
    wrefresh(win);
}

int main(int argc, char **argv) {
    Minefield field(10, 10);
    GameState state = NotStarted;
    
    field.plantMines(10, 0, 0);
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
        
    int win_h = 10, win_w = 20, win_y0 = (LINES - win_h)/2, win_x0 = (COLS - win_w) / 2;
    WINDOW * win = newwin(win_h, win_w, win_y0, win_x0);
    keypad(win, TRUE);
//     wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
    drawField(win, field);
    MEVENT mouseEvent;
    for(int c = wgetch(win); ; c = wgetch(win)) {
        switch(c) {
            case KEY_MOUSE:
//                     std::cout << '\a' << std::flush;
//                     mvaddstr(0, 0, "Received mouse event");
//                     refresh();
//                 if(getmouse(&mouseEvent) == OK) {
                    getmouse(&mouseEvent);
                    if(mouseEvent.bstate & BUTTON1_RELEASED) {
                        int y = mouseEvent.y - win_y0, x = (mouseEvent.x - win_x0)/2;
//                         mvprintw(0, 0, "Received click at %i,%i", y, x);
//                         refresh();
                        switch(state) {
                            case NotStarted:
                                field.plantMines(10, y, x);
                                field.reveal(y, x);
                                state = Running;
                                drawField(win, field);
                                break;
                            case Running:
                                if(field.reveal(y, x)) {
                                    mvprintw(0, 0, "Game lost!");
                                    for(Square & sq: field) sq.setState(Square::Open);
                                }
                                drawField(win, field);
                                break;
                            case Over:
                                break;
                        }
                        field.reveal(y, x);
                        drawField(win, field);
//                         wrefresh(win);
                        refresh();
                    }
                    else if(mouseEvent.bstate & BUTTON3_RELEASED) {
                        int y = mouseEvent.y - win_y0, x = (mouseEvent.x - win_x0)/2;
//                         mvprintw(0, 0, "Received right click at %i,%i", y, x);
//                         refresh();
                        field.toggleFlag(y, x);
                        drawField(win, field);
                    }
//                 }
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
