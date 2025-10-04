#ifndef WHATEVER_HPP
#define WHATEVER_HPP

// Swap: swaps the values of two given arguments.
template <typename T>
void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

// min: returns the smallest of two values.
// If the two values are equal, returns the second one.
template <typename T>
const T &min(const T &a, const T &b) {
    return (a < b) ? a : b; // When a == b, (a < b) is false, so b is returned.
}

// max: returns the largest of two values.
// If the two values are equal, returns the second one.
template <typename T>
const T &max(const T &a, const T &b) {
    return (a > b) ? a : b; // When a == b, (a > b) is false, so b is returned.
}

#endif // WHATEVER_HPP
