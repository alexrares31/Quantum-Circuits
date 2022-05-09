#ifndef MATRIX_HPP
#define MATRIX_HPP

#ifndef Complex
#include <complex>
#define Complex std::complex<double>
#endif

class Matrix
{
private:
    friend std::ostream& operator<<(
        std::ostream& os,
        const Matrix& mtrx
    );
    friend Matrix kron(const Matrix& a,
        const Matrix& b);
protected:
    Complex* mtrx_data;
    size_t rows;
    size_t cols;
    size_t last_filled_row;
public:
    Matrix();
    Matrix(size_t r, size_t c);
    virtual ~Matrix();
    Matrix(const Matrix& other);
    virtual Matrix& operator=(const Matrix& other);
    Matrix(Matrix&& other);
    virtual Matrix& operator=(Matrix&& other);
    size_t get_rows() const;
    size_t get_cols() const;
    size_t get_size() const;
    size_t index(size_t m, size_t n) const;
    Complex& operator()(size_t m, size_t n) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Complex& c) const;
    virtual Matrix operator*(const Matrix& other) const;
    Matrix operator/(const Complex& c) const;
    Matrix get_reduced_matrix(size_t m,
        size_t n) const;
    Complex determinant(Matrix submtrx) const;
    // virtual Complex foo() const;
};

#endif