#include <iostream>

#include <cstdlib>
#include <ctime>

#include "minefield.hpp"

int main(int argc, char** argv) {
    Minefield field(10, 10);
    std::srand(std::time(nullptr));
    
    std::size_t y = rand() % 10;
    std::size_t x = rand() % 10;
    field.plantMines(15, y, x);
    
    if (field.reveal(y, x))
        std::cout << "Game lost!" << std::endl;

    std::cout << field.toString() << std::endl;
}
