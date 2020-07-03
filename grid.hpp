#ifndef GRID_HPP
#define GRID_HPP

#include <cassert>
#include <cstddef>
#include <string>
#include <sstream>
#include <stdexcept>


template <class Type>
class Grid {
public:
    Grid(std::size_t height, std::size_t width) {
        if(width == 0 || height == 0)
            throw std::invalid_argument("Grid::Grid(): Null width and/or height!");
        _array = new Type[width*height](); //Allocate and initialize
        _height = height;
        _width = width;
    }
    ~Grid() {
        delete [] _array;
    }
    
    Type & operator()(std::size_t row, std::size_t col) {
        if(row >= _height || col >= _width)
            throw std::out_of_range("Grid::operator(): Point out of range!");
        return _array[_index(row,col)];
    }
    
    Type const & operator()(std::size_t row, std::size_t col) const {
        if(row >= _height || col >= _width)
            throw std::out_of_range("Grid::operator(): Point out of range!");
        return _array[_index(row,col)];
    }
    
    inline std::size_t width() const {
        return _width;
    }
    inline std::size_t height() const {
        return _height;
    }
    
    std::string toString(std::string colSeparator="", std::string rowSeparator="\n") const {
        std::stringstream s;
        for (int i = 0;;) {
            for(int j = 0;;) {
                s << _array[_index(i,j)];
                if(++j == _width) break;
                else s << colSeparator;
            }
            if(++i == _height) break;
            else s << rowSeparator;
        }
        
        return s.str();
    }
    
protected:
    inline std::size_t _index(std::size_t row, std::size_t col) const{
        return row*_width + col;
    }
    
private:
    Type* _array;
    std::size_t _height, _width;
};

#endif
