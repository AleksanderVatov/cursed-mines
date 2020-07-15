#include "minefield.hpp"

#include <cstdlib>
#include <ctime>
#include <set>

Minefield::Minefield(std::size_t height, std::size_t width): Grid<Square>(height, width) {}

Minefield Minefield::generateRandom(std::size_t height, std::size_t width, int numberOfMines) {
    std::set<std::size_t> mines;
    std::size_t currentRandom;
    
    std::srand(std::time(nullptr));
    for(int i = 1; i <= numberOfMines; ++i) {
        do {
            currentRandom = std::rand() % (height * width);
        } while(mines.count(currentRandom) != 0);
        mines.insert(currentRandom);
    }

    Minefield field(height, width);
    for(size_t ind: mines) {
        field(ind).setMined(true);
        for(Square& n: field.neighbors(ind)) n.incrementSurroundingMines();
    }

    return field;
}

