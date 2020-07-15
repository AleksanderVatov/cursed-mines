#ifndef MINEFIELD_HPP
#define MINEFIELD_HPP

#include "grid.hpp"
#include "square.hpp"


class Minefield : public Grid<Square> {
public:
    Minefield(std::size_t height, std::size_t width);
        
    static Minefield generateRandom(std::size_t height, std::size_t width, int numberOfMines);
};
#endif // MINEFIELD_HPP
