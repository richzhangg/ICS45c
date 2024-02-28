#ifndef INT_ARRAY_HPP
#define INT_ARRAY_HPP

#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

class Array {
public:
    // Construct zero-length array.
    Array() : len{0}, buf{nullptr} {
	}

    // Construct array of given length.
    explicit Array(int len) : len{len}, buf{new int[len]} {
	}

    // Copy & move constructors (TODO: implement these).
    Array(const Array& other);
    Array(Array&& other) noexcept;

    // Swap two arrays (without allocations).
    // Note: now a friend function,
    // which is the more common way to do it.
    friend void swap(Array& lhs, Array& rhs) noexcept {
        std::swap(lhs.len, rhs.len);
        std::swap(lhs.buf, rhs.buf);
    }

    // Copy & move assignment (TODO: implement these).
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    // Destructor
    ~Array() {
        // TODO: implement this
    }

    // Get the length of the array.
    int length() const {
        return len;
    }

    // Get a particular element of the array
    // (TODO: add bounds check).
    int& operator[](int index) {
        return buf[index];
    }

	// Get a particular element of the array
	// (TODO: add bounds check).
    const int& operator[](int index) const {
        return buf[index];
    }

    // Set every element of the array to `val`
    // (TODO: implement this).
    void fill(int val);

private:
    int len;
    int* buf;

    bool in_bounds(int index) const {
        return index >= 0 && index < len;
    }
};

// Print array to `out` in a single line.
inline std::ostream& operator<<(std::ostream& out, const Array& array) {
    std::stringstream temp;
    // We don't want to set formatting flags globally.
    temp << std::setprecision(2) << std::fixed << std::right;
    for (int i = 0; i < array.length(); ++i) {
        temp << std::setw(8) << array[i];
    }
    out << temp.str();
    return out;
}

// Read array from `in`, entries should be separated by whitespace.
inline std::istream& operator>>(std::istream& in, Array& array) {
    for (int i = 0; i < array.length(); ++i) {
        in >> array[i];
    }

    return in;
}

#endif

