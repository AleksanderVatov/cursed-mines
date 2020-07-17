#include <curses.h>

#include <clocale>
#include <iostream>

#include "ui/screen.hpp"


int main(int argc, char **argv) {
    Screen().loop();
    
}
