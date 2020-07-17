#ifndef MINEFIELD_HPP
#define MINEFIELD_HPP

#include <set>

#include "grid.hpp"
#include "square.hpp"

class Game : public Grid<Square> {
public:
    enum State {
        NotStarted,
        Running,
        Lost,
        Won
};

    Game(std::size_t height, std::size_t width);
    Game(Game &&) = default;

    void plantMines(std::set<std::size_t> const & locations);
    void plantMines(unsigned int number, std::set<std::size_t> const & locationsToAvoid = std::set<std::size_t>());
    void plantMines(unsigned int number, std::size_t revealedY, std::size_t revealedX);
    
    State reveal(std::size_t y, std::size_t x);
    State revealUnflaggedNeighbors(std::size_t y, std::size_t x);
    void toggleFlag(std::size_t y, std::size_t x);
    
    inline State state() {return _state;}
    
    void start();
    void reset();
    
private:
    State _state;
    
};
#endif // MINEFIELD_HPP
