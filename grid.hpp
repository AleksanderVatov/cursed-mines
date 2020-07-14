#ifndef GRID_HPP
#define GRID_HPP

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>


template <class Type>
class Grid {
typedef std::pair<std::size_t, std::size_t> Position;
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
    
    Type & operator()(Position pos) {
        return operator()(pos.first, pos.second);
    }
    
    Type const & operator()(Position pos) const {
        return operator()(pos.first, pos.second);
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
    
    class Neighborhood {
    friend class Grid;
    public:
        class Iterator : public std::iterator<std::forward_iterator_tag, Type> {
        friend class Neighborhood;
        public:
            bool operator==(Iterator const & other) {
                return _pos == other._pos && _neighborhood == other._neighborhood;
            }
            
            bool operator!=(Iterator const & other) {
                return _pos != other._pos || _neighborhood != other._neighborhood;
            }
            Iterator& operator++() {
                std::size_t y = _neighborhood->_y, 
                            x = _neighborhood->_x, 
                            y_max = _neighborhood->_grid->_height - 1, 
                            x_max = _neighborhood->_grid->_width  - 1;
                switch(_pos) {
                    case -1: ++_pos;
                        if(y > 0) break;
                    case  0: ++_pos;
                        if(x < x_max && y > 0) break;
                    case  1: ++_pos;
                        if(x < x_max) break;
                    case  2: ++_pos;
                        if(x < x_max && y < y_max) break;
                    case  3: ++_pos;
                        if(y < y_max) break;
                    case  4: ++_pos;
                        if(x > 0 && y < y_max) break;
                    case  5: ++_pos;
                        if(x > 0) break;
                    case  6: ++_pos;
                        if(x > 0 && y > 0) break;
                    case  7: ++_pos;
                }
                return *this;
            }
            
            Type& operator*() {
                return _neighborhood->_grid->operator()(pos());
            }
            
            Position pos() const {
                std::size_t y = _neighborhood->_y, x = _neighborhood->_x;
                switch(_pos) {
                    case 0: --y;      break;
                    case 1: --y; ++x; break;
                    case 2:      ++x; break;
                    case 3: ++y; ++x; break;
                    case 4: ++y;      break;
                    case 5: ++y; --x; break;
                    case 6:      --x; break;
                    case 7: --y; --x; break;
                    case 8: throw std::out_of_range("Grid::Neighborhood::Iterator: out of range!");
                }
                return Position(y, x);
            }
            
        private:
            Iterator(Neighborhood * neighborhood, int8_t pos) {
                _neighborhood = neighborhood;
                _pos = pos;
            }
            
            Neighborhood * _neighborhood;
            int8_t _pos;
        };
        
        Iterator begin() {
            return ++Iterator(this, -1);
        }
        Iterator end() {
            return Iterator(this, 8);
        }
    private:
        Neighborhood(Grid<Type>* grid, std::size_t y, std::size_t x) {
            _grid = grid;
            _y = y;
            _x = x;
            
        }
        Grid<Type> * _grid;
        std::size_t _x, _y;
    };
    
    Neighborhood neighbors(std::size_t row, std::size_t col) {
        if(row >= _height || col >= _width)
            throw std::out_of_range("Grid::operator(): Point out of range!");
        return Neighborhood(this, row, col);
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
