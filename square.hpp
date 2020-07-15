#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <cstdint>
#include <ostream>

class Square {
    enum State {
        Closed = 0,
        Open = 1 << 4,
        Flagged = 2 << 4,
        QuestionMark = 3 << 4
    };
public:
    inline bool isMined() const {
        return _data & mine_mask;
    }
    
    inline void setMined(bool mined) {
        _data = (_data & ~mine_mask) | (mined << 7);
    }
    
    inline State state() const {
        return static_cast<State>(_data & state_mask);
    }
    
    inline void setState(State state) {
        _data = (_data & ~state_mask) | state;
    }
    
    inline uint_least8_t surroundingMines() const {
        return _data & surrounding_mines_mask;
    }
    
    inline void setSurroundingMines(uint_least8_t surroundingMines) {
        _data = (_data & ~surrounding_mines_mask) | surroundingMines;
    }
    
    inline void incrementSurroundingMines() {
        ++_data;
    }
    
    std::ostream & operator<<(std::ostream & os) {
        switch(state()) {
            case Open:
                if(isMined()) os << "\U0001F4A3";
                else os << surroundingMines();
                break;
            case Flagged:
                os << "\U0001F6A9";
                break;
            case QuestionMark:
                os << "\U00002753";
                break;
            case Closed:
            default:
                os << "\U000025a1";
                break;
        }
    }
    
private:
    static const uint_least8_t mine_mask = 0b01000000;
    static const uint_least8_t state_mask = 0b00110000;
    static const uint_least8_t surrounding_mines_mask = 0b00001111;
    uint8_t _data = 0;
};

#endif // SQUARE_HPP
