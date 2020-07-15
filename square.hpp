#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <bitset>
#include <cstdint>
#include <iostream>

class Square {
public:
    enum State {
        Closed = 0,
        Open = 1 << 4,
        Flagged = 2 << 4,
        QuestionMark = 3 << 4
    };
    
    inline bool isMined() const {
        return _data & mine_mask;
    }
    
    inline void setMined(bool mined) {
        _data = (_data & ~mine_mask) | (mined << 6);
    }
    
    inline State state() const {
        return static_cast<State>(_data & state_mask);
    }
    
    inline void setState(State state) {
        _data = (_data & ~state_mask) | state;
        std::cerr << std::bitset<8>(_data) << std::endl;
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
    
    
private:
    static const uint_least8_t mine_mask = 0b01000000;
    static const uint_least8_t state_mask = 0b00110000;
    static const uint_least8_t surrounding_mines_mask = 0b00001111;
    uint_least8_t _data = 0;
};

std::ostream & operator<<(std::ostream & os, Square sq);

#endif // SQUARE_HPP
