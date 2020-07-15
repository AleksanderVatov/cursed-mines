#include <iostream>

#include <cstdlib>
#include <ctime>


#include "minefield.hpp"

int main(int argc, char** argv) {
    Minefield field = Minefield::generateRandom(10, 10, 15);
    std::srand(std::time(nullptr));
    field.reveal(rand() % 10, rand() % 10);
//     for(Square& sq: field) sq.setState(Square::Open);
    std::cout << field.toString() << std::endl;
}
