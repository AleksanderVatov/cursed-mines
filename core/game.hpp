#ifndef MINEFIELD_HPP
#define MINEFIELD_HPP

#include <set>

#include "grid.hpp"
#include "square.hpp"

class Game : protected Grid<Square> {
public:
    enum State {
        NotStarted,
        Running,
        Lost,
        Won
};

    Game(std::size_t height, std::size_t width);
    Game(Game &&) = default;
    
    unsigned numberOfMines() const;
    unsigned numberOfFlags() const;
    
    void create(unsigned numberOfMines, std::size_t revealedY, std::size_t revealedX);
    State reveal(std::size_t y, std::size_t x);
    State revealUnflaggedNeighbors(std::size_t y, std::size_t x);
    State toggleFlag(std::size_t y, std::size_t x);
    
    inline State state() {return _state;}
    
    void start();
    void clear();
    
    Square const * begin() const;
    Square const * end() const;
    Square const * row_begin(std::size_t row) const;
    Square const * row_end(std::size_t row) const;
    
    using Grid<Square>::get; // Get *const* reference to Square at position y, x
    using Grid<Square>::height;
    using Grid<Square>::width;
    
protected:
    void plantMines(std::set<std::size_t> const & locations);
    void plantMines(unsigned int number, std::set<std::size_t> const & locationsToAvoid = std::set<std::size_t>());
    void detectWin();
    
private:
    State _state;
    unsigned _openSquares = 0, _mines = 0, _flags = 0;
    
};
#endif // MINEFIELD_HPP
