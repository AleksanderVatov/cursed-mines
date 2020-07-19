#ifndef COLORSCHEME_HPP
#define COLORSCHEME_HPP


class ColorScheme {
public:
    enum Pair {
        Statusbar = 9,
        Menu = 10
    };
    static void initColors();
};
#endif // COLORSCHEME_HPP
