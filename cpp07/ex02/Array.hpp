#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>

template <typename T>
class Array {
public:
    Array() : _array(NULL), _size(0) {}

    Array(unsigned int n) : _array(NULL), _size(n) {
        if (n > 0)
            _array = new T[n]();
    }

    Array(const Array &other) : _array(NULL), _size(other._size) {
        if (_size > 0) {
            _array = new T[_size]();
            for (unsigned int i = 0; i < _size; i++) {
                _array[i] = other._array[i];
            }
        }
    }

    Array &operator=(const Array &other) {
        if (this != &other) {
            if (_array)
                delete [] _array;
            _size = other._size;
            if (_size > 0) {
                _array = new T[_size]();
                for (unsigned int i = 0; i < _size; i++) {
                    _array[i] = other._array[i];
                }
            } else {
                _array = NULL;
            }
        }
        return *this;
    }

    ~Array() {
        if (_array)
            delete [] _array;
    }

    T &operator[](unsigned int index) {
        if (index >= _size)
            throw std::exception();
        return _array[index];
    }

    const T &operator[](unsigned int index) const {
        if (index >= _size)
            throw std::exception();
        return _array[index];
    }

    unsigned int size() const {
        return _size;
    }

private:
    T*           _array;
    unsigned int _size;
};

#endif
