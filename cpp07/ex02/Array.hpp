#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>

// Template class Array: a dynamically allocated array of elements of type T.
template <typename T>
class Array {
public:
    // Default constructor: creates an empty array.
    Array() : _array(NULL), _size(0) {}

    // Constructor with an unsigned int n: creates an array of n default-initialized elements.
    Array(unsigned int n) : _array(NULL), _size(n) {
        if (n > 0)
            _array = new T[n](); // Using () for value initialization.
    }

    // Copy constructor: performs a deep copy.
    Array(const Array &other) : _array(NULL), _size(other._size) {
        if (_size > 0) {
            _array = new T[_size]();
            for (unsigned int i = 0; i < _size; i++) {
                _array[i] = other._array[i];
            }
        }
    }

    // Assignment operator: performs a deep copy.
    Array &operator=(const Array &other) {
        if (this != &other) {
            // Clean up current array.
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

    // Destructor: deallocates the array.
    ~Array() {
        if (_array)
            delete [] _array;
    }

    // Subscript operator (non-const): provides access to array elements.
    // Throws std::exception if the index is out of bounds.
    T &operator[](unsigned int index) {
        if (index >= _size)
            throw std::exception();
        return _array[index];
    }

    // Subscript operator (const version): for read-only access.
    const T &operator[](unsigned int index) const {
        if (index >= _size)
            throw std::exception();
        return _array[index];
    }

    // Returns the number of elements in the array.
    unsigned int size() const {
        return _size;
    }

private:
    T*           _array;
    unsigned int _size;
};

#endif // ARRAY_HPP
