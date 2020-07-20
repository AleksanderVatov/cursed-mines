#ifndef COLORSCHEME_HPP
#define COLORSCHEME_HPP


class ColorScheme {
public:
    enum Pair {
        Border = 9,
        Statusbar = 10,
        Menu = 11
    };
    static void initColors();
};
#endif // COLORSCHEME_HPP
