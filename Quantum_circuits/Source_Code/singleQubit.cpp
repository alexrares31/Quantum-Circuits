#include "singleQubit.hpp"
#include <cmath>
#include <stdexcept>

#ifndef Complex
#include <complex>
#define Complex std::complex<double>
#endif

SingleQubit::SingleQubit() : Matrix{2, 1}
{
    mtrx_data[0] = Complex{1, 0};
    mtrx_data[1] = Complex{0, 0};
}

SingleQubit::SingleQubit(const Complex& c1,
    const Complex& c2) : Matrix{2, 1}
{
    double norm_const;
    norm_const = std::sqrt(std::pow(std::abs(c1), 2)
        + std::pow(std::abs(c2), 2));
    mtrx_data[0] = c1 / norm_const;
    mtrx_data[1] = c2 / norm_const;
}

SingleQubit::~SingleQubit() {}

SingleQubit& SingleQubit::operator=(const Matrix& other)
{
    if (other.get_rows() != 2 || other.get_cols() != 1)
        throw std::out_of_range(
            "Dimensions don't match.");
    else
        if (&other == this) {
            return *this;
        } else {
            delete[] mtrx_data;
            mtrx_data = new Complex[2];
            mtrx_data[0] = other(0, 0);
            mtrx_data[1] = other(1, 0);
        }

    return *this;
}