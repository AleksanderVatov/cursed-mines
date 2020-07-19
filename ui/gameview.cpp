#include "gameview.hpp"

constexpr const char* GameView::SURROUNDING_STRINGS[];

GameView::GameView(int height, int width, int y0, int x0) : Widget(height, width, y0, x0) {
    
}


void GameView::setGame(Game* game) {
    _game = game;
}

int GameView::maxGameHeight() const {
    return height();
}

int GameView::maxGameWidth() const {
    return width() / SQUARE_WIDTH;
}

void GameView::draw() {
    wmove(window(), 0, 0);
        for(Square const & sq: *_game) {
            switch(sq.state()) {
                case Square::Open:
                    if(sq.isMined()) 
                        waddstr(window(), "💥");
                    else {
                        auto surroundingMines = sq.surroundingMines();
                        wattron(window(), COLOR_PAIR(surroundingMines));
                        waddstr(window(), SURROUNDING_STRINGS[surroundingMines]);
                        wattroff(window(), COLOR_PAIR(surroundingMines));
                    }
                    break;
                case Square::Flagged:
                    waddstr(window(), "🚩");
                    break;
                case Square::QuestionMark:
                    waddstr(window(), "❔");
                    break;
                case Square::Closed:
                default:
                    waddstr(window(), "⬛");
                    break;
            }
        }
//         move(0,0);
        wrefresh(window());
}

bool GameView::mouseEvent (MEVENT* event) {
    int y = event->y - y0();
    int x = (event->x - x0()) / SQUARE_WIDTH;
    if(y < 0 || y >= _game->height() || x < 0 || x > _game->width()) return false;
    
    if(event->bstate & (BUTTON1_CLICKED | BUTTON1_PRESSED)) {
        switch(_game->state()) {
            case Game::NotStarted:
                _game->plantMines(0.15*(_game->height()*_game->width()), y, x);
                _game->reveal(y, x);
                _game->start();
                draw();
                break;
            case Game::Running:
                if(_game->get(y, x).state() == Square::Open) break; // Avoid redrawing unnecessarily
                if(_game->reveal(y, x) == Game::Lost) {
                    mvprintw(0, 0, "Game lost!");
                    for(Square & sq: *_game) sq.setState(Square::Open);
                }
                draw();
                break;
            case Game::Lost:
            case Game::Won:
                break;
        }
        return true;
    }
    else if(event->bstate & (BUTTON3_CLICKED | BUTTON3_PRESSED)) {
//                         mvprintw(0, 0, "Received right click at %i,%i", y, x);
//                         refresh();
        _game->toggleFlag(y, x);
        draw();
        return true;
    }
    else if(event->bstate & BUTTON1_DOUBLE_CLICKED) {
        if(_game->revealUnflaggedNeighbors(y, x) == Game::Lost) {
            mvprintw(0, 0, "Game lost!");
        }
        draw();
        return true;
    }
    return false;
}
