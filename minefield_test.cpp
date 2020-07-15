#include<iostream>

#include "minefield.hpp"

int main(int argc, char** argv) {
    Minefield field = Minefield::generateRandom(10, 10, 15);
    for(Square& sq: field) sq.setState(Square::Open);
    std::cout << field.toString() << std::endl;
}
