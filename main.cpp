#include <curses.h>

#include <clocale>

#include "minefield.hpp"

int main(int argc, char **argv) {
    Minefield field(10, 10);
    field.plantMines(10, 0, 0);
//     field.reveal(0, 0);
    for(Square & sq: field) sq.setState(Square::Open);
    
    //Set up curses
    std::setlocale(LC_ALL, "");
    initscr();
    cbreak(); // Read characters one at a time
    noecho(); // Do not write input characters to screen
    nodelay(stdscr, TRUE); // Make getch return ERR in the absence of input rather than waiting
    curs_set(0); // Hide cursor
    refresh(); // Apparently a refresh is needed after initscr.
        
    int win_h = 10, win_w = 10;
    WINDOW * win = newwin(win_h, win_w, (LINES - win_h)/2, (COLS - win_w) / 2);
//     wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
    for(Square sq: field) {
        switch(sq.state()) {
            case Square::Open:
                if(sq.isMined()) 
//                     waddstr(win, "💥"); //Too wide
//                     waddstr(win, "💣"); //Too wide
                    waddch(win, ACS_BLOCK); 
                else waddch(win, '0' + sq.surroundingMines());
                break;
            case Square::Flagged:
                wprintw(win, "\U0001F6A9");
//                 waddstr(win, "\U0001F6A9");
                break;
            case Square::QuestionMark:
                waddch(win, '?');
//                 waddstr(win, "\U00002753");
                break;
            case Square::Closed:
            default:
                waddch(win, 'X');
//                 waddstr(win, "\U000025a1");
                break;
        }
    }
    wrefresh(win);
    while(getch() == ERR);
    endwin();
    return 0;
}
