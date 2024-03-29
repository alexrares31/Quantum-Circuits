#include "matrix.hpp"
#include <stdexcept>

Matrix::Matrix() :
    rows{0},
    cols{0},
    mtrx_data{nullptr} {}

Matrix::Matrix(size_t r, size_t c) :
    rows{r},
    cols{c},
    mtrx_data{new Complex[r * c]} {}

Matrix::~Matrix()
{
    delete[] mtrx_data;
}

size_t Matrix::get_rows() const
{
    return rows;
}

size_t Matrix::get_cols() const
{
    return cols;
}

size_t Matrix::get_size() const
{
    return rows * cols;
}

size_t Matrix::index(size_t m, size_t n) const
{
    if (m >= 0 && m < rows && n >= 0 && n < cols)
        return n + m * cols;
    else
        throw std::out_of_range(
            "Out of range error.");
}

Complex& Matrix::operator()(size_t m, size_t n) const
{
    return mtrx_data[index(m, n)];
}

Matrix::Matrix(const Matrix& other)
{
    rows = other.rows;
    cols = other.cols;
    mtrx_data = new Complex[rows * cols];
    for (size_t i{0}; i < rows; i++)
        for (size_t j{0}; j < cols; j++)
            mtrx_data[index(i, j)] = other(i, j);
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (&other == this) {
        return *this;
    } else {
        rows = other.rows;
        cols = other.cols;
        delete[] mtrx_data;
        mtrx_data = new Complex[rows * cols];
        for (size_t i{0}; i < rows; i++)
            for (size_t j{0}; j < cols; j++)
                mtrx_data[index(i, j)] = other(i, j);
    }

    return *this;
}

Matrix::Matrix(Matrix&& other)
{
    rows = other.rows;
    cols = other.cols;
    mtrx_data = other.mtrx_data;
    other.rows = 0;
    other.cols = 0;
    other.mtrx_data = nullptr;
}

Matrix& Matrix::operator=(Matrix&& other)
{
    std::swap(rows, other.rows);
    std::swap(cols, other.cols);
    std::swap(mtrx_data, other.mtrx_data);

    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const
{
    Matrix sum{rows, cols};
    if (rows == other.rows && cols == other.cols)
        for (size_t i{0}; i < rows; i++)
            for (size_t j{0}; j < cols; j++)
                sum(i, j) = mtrx_data[index(i, j)]
                    + other(i, j);
    else
        throw std::out_of_range(
            "Dimensions don't match.");

    return sum;
}

Matrix Matrix::operator*(const Complex& c) const
{
    Matrix product{rows, cols};
    for (size_t i{0}; i < rows; i++)
        for (size_t j{0}; j < cols; j++)
            product(i, j) =
                mtrx_data[index(i, j)] * c;
    return product;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    Matrix product{rows, other.cols};
    if (cols == other.rows)
        for (size_t i{0}; i < rows; i++)
            for (size_t j{0}; j < other.cols; j++)
                for (size_t k{0}; k < cols; k++)
                    product(i, j) += 
                        mtrx_data[index(i, k)]
                        * other(k, j);
    else
        throw std::out_of_range(
            "Dimensions don't match.");

    return product;
}

Matrix Matrix::operator/(const Complex& c) const
{
    Matrix product{rows, cols};
    for (size_t i{0}; i < rows; i++)
        for (size_t j{0}; j < cols; j++)
            product(i, j) =
                mtrx_data[index(i, j)] / c;
    return product;
}

std::ostream& operator<<(
    std::ostream &os, const Matrix &mtrx)
{
    for (size_t i{0}; i < mtrx.rows; i++) {
        for (size_t j{0}; j < mtrx.cols; j++)
            os << mtrx(i, j) << ' ';
        os << '\n';
    }

    return os;
}

Matrix kron(const Matrix& a, const Matrix& b)
{
    size_t arows = a.get_rows();
    size_t acols = a.get_cols();
    size_t brows = b.get_rows();
    size_t bcols = b.get_cols();
    Matrix product{arows * brows, acols * bcols};
    for (size_t i{0}; i < arows; i++)
        for (size_t j{0}; j < acols; j++)
            for (size_t k{0}; k < brows; k++)
                for (size_t l{0}; l < bcols; l++)
                    product(i*brows + k, j*bcols + l) = 
                        a(i, j) * b(k, l);
    
    return product;
}