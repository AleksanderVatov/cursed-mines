#include "app.hpp"
#include "colorscheme.hpp"
#include "gameview.hpp"

#include <algorithm>

constexpr const char* GameView::SURROUNDING_STRINGS[];

GameView::GameView(int height, int width, int y0, int x0)
    : Widget(height, width, y0, x0) {
    _game = nullptr;
}

void GameView::setGame(Game* game) {
    _game = game;
    calculateLayout();
}

int GameView::maxGameHeight() const {
    return height() - 2;
}

int GameView::maxGameWidth() const {
    return (width() / SQUARE_WIDTH) - 1;
}

void GameView::draw() {
    wattron(window(), COLOR_PAIR(ColorScheme::Border));
    wborder(window(), 0, 0, 0, 0, 0, 0, 0, 0);
    wattroff(window(), COLOR_PAIR(ColorScheme::Border));
    if(!_game) return;
    if(_game->state() == Game::Running || _game->state() == Game::NotStarted) {
        for(int row = 0; row < _maxRows; ++row) {
            wmove(window(), field_y0 + row, field_x0);
            for(int col = 0; col < _maxCols; ++col) {
                Square const & sq = _game->get(row, col);
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
                    case Square::Closed:
                        waddstr(window(), "⬛");
                        break;
                    case Square::Flagged:
                        waddstr(window(), "🚩");
                        break;
                    case Square::QuestionMark:
                        waddstr(window(), "❔");
                        break;
                }
            }
        }
    }
    else {
    // If game is over
        for(int row = 0; row < _maxRows; ++row) {
            wmove(window(), field_y0 + row, field_x0);
            for(int col = 0; col < _maxCols; ++col) {
                Square const & sq = _game->get(row, col);
                switch(sq.state()) {
                    case Square::Open:
                    case Square::Closed:
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
                    case Square::QuestionMark:
                        if(sq.isMined())
                            waddstr(window(), "✅");
                        else
                            waddstr(window(), "❌");
                        
                        break;
                }
            }
        }
    }
    wrefresh(window());
}

bool GameView::mouseEvent(MEVENT* event) {
    int y = event->y - y0() - field_y0;
    int x = (event->x - x0() - field_x0) / SQUARE_WIDTH;
    if(y < 0 || y >= _game->height() || x < 0 || x > _game->width()) return false;
    
    if(event->bstate & (BUTTON1_CLICKED | BUTTON1_PRESSED)) {
        switch(_game->state()) {
            case Game::NotStarted:
                _game->create(0.15*(_game->height()*_game->width()), y, x);
                _game->reveal(y, x);
                _game->start();
                App::statusbar()->update();
                draw();
                break;
            case Game::Running:
                if(_game->get(y, x).state() == Square::Open) break; // Avoid redrawing unnecessarily
                updateGameStateDescription(_game->reveal(y, x));
                App::statusbar()->update();
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
        
        updateGameStateDescription(_game->toggleFlag(y, x));
        App::statusbar()->update();
        draw();
        return true;
    }
    else if(event->bstate & BUTTON1_DOUBLE_CLICKED) {
        updateGameStateDescription(_game->revealUnflaggedNeighbors(y, x));
        draw();
        return true;
    }
    return false;
}

void GameView::calculateLayout() {
    _maxRows = std::min<std::size_t>(height(), maxGameHeight());
    _maxCols = std::min<std::size_t>(width(), maxGameWidth());
    field_y0 = 1;
    field_x0 = 1;
}

void GameView::updateGameStateDescription(Game::State state) {
    switch(state) {
        case Game::Won:
            App::statusbar()->setText("Game won!");
            break;
        case Game::Lost:
            App::statusbar()->setText("Game lost!");
            break;
        default:
            break;
    }
}

