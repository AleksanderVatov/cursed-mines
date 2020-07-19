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

    void plantMines(std::set<std::size_t> const & locations);
    void plantMines(unsigned int number, std::set<std::size_t> const & locationsToAvoid = std::set<std::size_t>());
    void plantMines(unsigned int number, std::size_t revealedY, std::size_t revealedX);
    
    State reveal(std::size_t y, std::size_t x);
    State revealUnflaggedNeighbors(std::size_t y, std::size_t x);
    void toggleFlag(std::size_t y, std::size_t x);
    
    inline State state() {return _state;}
    
    void start();
    void reset();
    
    Square const * begin() const;
    Square const * end() const;
    
    using Grid<Square>::get; // Get *const* reference to Square at position y, x
    using Grid<Square>::height;
    using Grid<Square>::width;
    
private:
    State _state;
    
};
#endif // MINEFIELD_HPP
