#include "minefield.hpp"

#include <cstdlib>
#include <ctime>
#include <queue>
#include <set>

#include <iostream>

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

void Minefield::reveal(std::size_t y, std::size_t x) {
    //The non-recursive version of the flood fill algorithm (sometimes called forest fire) is used
    std::queue<std::size_t> q;
    Neighborhood neighborhood = neighbors(y, x);
    std::size_t clickedIndex = flatIndex(y,x);
    Square & clickedSquare = (*this)(clickedIndex);
    if(clickedSquare.state() == Square::Open) //Nothing to do
        return;
    clickedSquare.setState(Square::Open);
    if(clickedSquare.isMined() || clickedSquare.surroundingMines() != 0) // We're done here
        return;
    
    q.push(clickedIndex); //Push the clicked square to q
    for(Neighborhood::Iterator it = neighborhood.begin(); it != neighborhood.end(); ++it)
        q.push(it.flatIndex());
    
    for(; !q.empty(); q.pop()) {
        size_t currentIndex = q.front();
        Square& currentSquare = (*this)(currentIndex);
        
        Position pos = unravelIndex(currentIndex);
        std::cerr << "Popping " << pos.first << ", " << pos.second << '\n';
        
        if(currentSquare.surroundingMines() != 0) continue;
        auto neighborsNeighborhood = neighbors(currentIndex);
        for(auto it = neighborsNeighborhood.begin(); it != neighborsNeighborhood.end(); ++it) {
            if(it->state() == Square::Closed) {
                it->setState(Square::Open);
                q.push(it.flatIndex());
                
                Position pos2 = unravelIndex(it.flatIndex());
                std::cerr << "Pushing " << pos2.first << ", " << pos2.second << '\n';
            }
        }
    }
}
