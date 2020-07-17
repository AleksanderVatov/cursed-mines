#include "game.hpp"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <set>

Game::Game(std::size_t height, std::size_t width): Grid<Square>(height, width) {}


void Game::plantMines(std::set<std::size_t> const & locations) {
    for(size_t ind: locations) {
        Square& sq = (*this)(ind);
        if(!sq.isMined()) {
            sq.setMined(true);
            for(Square& n: neighbors(ind)) n.incrementSurroundingMines();
        }
    }
    
};

void Game::plantMines(unsigned int number, std::set<std::size_t> const& locationsToAvoid) {
    std::set<std::size_t> locations;
    std::size_t currentRandom;
    std::size_t size = height() * width();
    
    std::srand(std::time(nullptr));
    for(int i = 1; i <= number; ++i) {
        do {
            currentRandom = std::rand() % size;
        } while(locations.count(currentRandom) != 0 || locationsToAvoid.count(currentRandom) != 0);
        locations.insert(currentRandom);
    }
    
    plantMines(locations);
}

void Game::plantMines(unsigned int number, std::size_t revealedY, std::size_t revealedX) {
    std::set<std::size_t> locationsToAvoid;
    locationsToAvoid.insert(flatIndex(revealedY, revealedX));
    
    auto neighborhood = neighbors(revealedY, revealedX);
    for(auto it = neighborhood.begin(); it != neighborhood.end(); ++it)
        locationsToAvoid.insert(it.flatIndex());
    
    plantMines(number, locationsToAvoid);
}


bool Game::reveal(std::size_t y, std::size_t x) {
    //The non-recursive version of the flood fill algorithm (sometimes called forest fire) is used
    std::queue<std::size_t> q;
    Neighborhood neighborhood = neighbors(y, x);
    std::size_t clickedIndex = flatIndex(y,x);
    Square & clickedSquare = (*this)(clickedIndex);
    if(clickedSquare.state() == Square::Open) //Nothing to do
        return false; // If there was a mine here, it was already detonated
    clickedSquare.setState(Square::Open);
    if(clickedSquare.isMined()) return true;
    if(clickedSquare.surroundingMines() != 0) return false;
    
    q.push(clickedIndex); //Push the clicked square to q
    for(Neighborhood::Iterator it = neighborhood.begin(); it != neighborhood.end(); ++it)
        q.push(it.flatIndex());
    
    for(; !q.empty(); q.pop()) {
        size_t currentIndex = q.front();
        Square& currentSquare = (*this)(currentIndex);
        if(currentSquare.surroundingMines() != 0) continue;
        
        auto neighborsNeighborhood = neighbors(currentIndex);
        for(auto it = neighborsNeighborhood.begin(); it != neighborsNeighborhood.end(); ++it) {
            if(it->state() == Square::Closed) {
                it->setState(Square::Open);
                q.push(it.flatIndex());
            }
        }
    }
    return false;
}

bool Game::revealUnflaggedNeighbors(std::size_t y, std::size_t x) {
    bool lostGame = false;
    for(Square & sq: neighbors(y, x)) {
        if(sq.state() == Square::Closed) {
            sq.setState(Square::Open);
            if(sq.isMined()) lostGame = true;
            else if(sq.surroundingMines() == 0) reveal(y, x);
        }
    }
    return lostGame;
}


void Game::toggleFlag(std::size_t y, std::size_t x) {
    Square & sq = (*this)(y, x);
    switch(sq.state()) {
        case Square::Closed:
        case Square::QuestionMark:
            sq.setState(Square::Flagged);
            break;
        case Square::Flagged:
            sq.setState(Square::Closed);
            break;
        case Square::Open:
            break;
    }
}

void Game::reset() {
    std::fill(begin(), end(), Square());
}
