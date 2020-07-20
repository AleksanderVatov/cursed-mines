#include <curses.h>

#include <clocale>
#include <iostream>

#include "ui/app.hpp"

int main(int argc, char **argv) {
    App().run();
}
