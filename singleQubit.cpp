#include "singleQubit.hpp"
#include <cmath>

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
    double normalization_const;
    normalization_const = sqrt(pow(std::abs(c1), 2)
        + pow(std::abs(c2), 2));
    mtrx_data[0] = c1 / normalization_const;
    mtrx_data[1] = c2 / normalization_const;
}

SingleQubit::~SingleQubit() {}

SingleQubit& SingleQubit::operator=(const Matrix& other)
{
    if (other.get_rows() != 2 || other.get_cols() != 1)
        throw "Dimensions don't match.";
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