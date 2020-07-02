#ifndef GRID_HPP
#define GRID_HPP

#include <cassert>
#include <cstddef>
#include <string>
#include <sstream>


template <class Type>
class Grid {
public:
    Grid(std::size_t height, std::size_t width) {
        assert(height > 0 && width > 0);
        _array = new Type[width*height];
        _height = height;
        _width = width;
    }
    ~Grid() {
        delete [] _array;
    }
    
    Type & operator()(std::size_t row, std::size_t col) {
        return _array[_index(row,col)];
    }
    
    Type const & operator()(std::size_t row, std::size_t col) const {
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
