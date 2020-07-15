#include <ostream>

#include "square.hpp"

std::ostream & operator<<(std::ostream & os, Square sq) {
        switch(sq.state()) {
            case Square::Open:
                if(sq.isMined()) os << "\U0001F4A3";
                else os << int(sq.surroundingMines());
                break;
            case Square::Flagged:
                os << "\U0001F6A9";
                break;
            case Square::QuestionMark:
                os << "\U00002753";
                break;
            case Square::Closed:
            default:
                os << "\U000025a1";
                break;
        }
        return os;
    }
