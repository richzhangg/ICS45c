#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "array.hpp"

template <typename T>
class Matrix {
public:
    // Construct 0x0 matrix
    Matrix() : rows(0), cols(0), data() {}

    // Construct matrix with given number of rows and columns
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows) {
        for (int i = 0; i < rows; ++i) {
            data[i] = Array<T>(cols);
        }
    }

    // Get a particular row of the matrix
    Array<T>& operator[](int row) {
        return data[row];
    }

    const Array<T>& operator[](int row) const {
        return data[row];
    }

    // Get number of rows / columns
    int num_rows() const { return rows; }
    int num_cols() const { return cols; }

    // Fill every entry of the matrix with given value 'val'
    void fill(const T& val) {
        for (int i = 0; i < rows; ++i) {
            data[i].fill(val);
        }
    }

    // Fill matrix, set entry in row `i` and column `j`
    // to `fn(i, j)`
    template <typename Fn>
    void fill_with_fn(Fn fn) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = fn(i, j);
            }
        }
    }

private:
    int rows, cols;
    Array<Array<T>> data;
};

// Print matrix to `out`
template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
    for (int i = 0; i < matrix.num_rows(); ++i) {
        for (int j = 0; j < matrix.num_cols(); ++j) {
            if (j > 0) out << " ";
            out << matrix[i][j];
        }
        out << "\n";
    }
    return out;
}

// Read matrix from `in`
template <typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix) {
    for (int i = 0; i < matrix.num_rows(); ++i) {
        for (int j = 0; j < matrix.num_cols(); ++j) {
            in >> matrix[i][j];
        }
    }
    return in;
}

#endif

