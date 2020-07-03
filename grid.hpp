#ifndef GRID_HPP
#define GRID_HPP

#include <cassert>
#include <cstddef>
#include <iterator>
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
    
    Grid(Grid<Type> &&) = default;
    
    ~Grid() {
//         std::cerr << "Deconstructing Grid with _array = " << (void*)_array;
        if(_array) delete [] _array;
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
    
    bool operator==(Grid<Type> const & other) const {
        if (_height != other._height || _width != other._width) return false;
        for (int i = 0; i < _height*_width; ++i)
            if(_array[i] != other._array[i])
                return false;
        return true;
    }
    
    inline std::size_t width() const {
        return _width;
    }
    inline std::size_t height() const {
        return _height;
    }
    
    Type * begin() {
        return _array;
    }
    
    Type const * begin() const {
        return _array;
    }
    
    Type * end() {
        return _array + _height*_width;
    }
    
    Type const * end() const{
        return _array + _height*_width;
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
    
    static Grid<Type> fromArray(Type array[], std::size_t height, std::size_t width) {
        Grid<Type> g(height, width);
        for(int i = 0; i < height*width; ++i) g._array[i] = array[i];
        return g;
    }
    
    
    static Grid<Type> fromString(std::string s, std::size_t height, std::size_t width) {
        std::stringstream ss;
        ss.str(s);
        Grid<Type> g(height, width);
        Type t;
        for(int i = 0; i < height*width; ++i) {
            if (ss >> t) g._array[i] = t;
            else break;
        }
        return g;
    }
    
    
protected:
    inline std::size_t _index(std::size_t row, std::size_t col) const{
        return row*_width + col;
    }
    
private:
    Type * _array;
    std::size_t _height, _width;
};

#endif
