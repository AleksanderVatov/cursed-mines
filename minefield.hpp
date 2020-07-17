#ifndef MINEFIELD_HPP
#define MINEFIELD_HPP

#include <set>

#include "grid.hpp"
#include "square.hpp"

class Minefield : public Grid<Square> {
public:
    Minefield(std::size_t height, std::size_t width);
    Minefield(Minefield &&) = default;
        
    bool reveal(std::size_t y, std::size_t x);
    void toggleFlag(std::size_t y, std::size_t x);
    
    void plantMines(std::set<std::size_t> const & locations);
    void plantMines(unsigned int number, std::set<std::size_t> const & locationsToAvoid = std::set<std::size_t>());
    void plantMines(unsigned int number, std::size_t revealedY, std::size_t revealedX);
    
protected:
//     using Grid<Square>::operator();
    
};
#endif // MINEFIELD_HPP
