#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

template <typename T>
class Array {
public:
    Array() : len(0), buf(nullptr) {}
    
    explicit Array(int len) : len(len), buf(new T[len]) {}

    Array(const Array& other) : len(other.len), buf(new T[other.len]) {
        for (int i = 0; i < len; ++i)
            buf[i] = other.buf[i];
    }

    Array(Array&& other) noexcept {
        len = other.len;
        buf = other.buf;
        other.buf = nullptr;
    }

	friend void swap(Array& lhs, Array& rhs) noexcept {
        std::swap(lhs.len, rhs.len);
        std::swap(lhs.buf, rhs.buf);
    }

    Array& operator=(const Array& other) {
    	if (this != &other) {
        	Array temp(other);
        	swap(*this, temp);
    	}
    	return *this;
	}

    Array& operator=(Array&& other) noexcept {
        swap(*this, other);
        return *this;    
	}

	~Array() {
		delete[] buf;
	}

    int length() const { 
		return len; 
	}

    T& operator[](int index) {
        if (!in_bounds(index)) {
            throw std::string("Exception operator[](" + std::to_string(index) + ") Out Of Range");
        }
        return buf[index];
    }

    const T& operator[](int index) const {
        if (!in_bounds(index)) {
            throw std::string("Exception operator[](" + std::to_string(index) + ") Out Of Range");
        }
        return buf[index];
    }

    // Fill array by setting every entry `i` to `fn(i)`.
    template <typename Fn>
    void fill_with_fn(Fn fn) {
        for (int i = 0; i < len; ++i) {
            buf[i] = fn(i);
        }
    }

	void fill(T val) {
    for (int i = 0; i < len; ++i) {
        buf[i] = val;
    }
	}


private:
    int len;
    T* buf;

    bool in_bounds(int index) const {
        return index >= 0 && index < len;
    }
};

// Print array to `out` in a single line.
template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& array) {
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
template <typename T>
std::istream& operator>>(std::istream& in, Array<T>& array) {
    for (int i = 0; i < array.length(); ++i) {
        in >> array[i];
    }

    return in;
}

#endif

