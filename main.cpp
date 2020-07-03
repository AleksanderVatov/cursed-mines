#include <iostream>

#include "grid.hpp"

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    auto g = Grid<char>::fromString("abcdef", 2, 3);
    for(auto c: g)
        std::cout << c;
    return 0;
}
