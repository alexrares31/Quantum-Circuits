#ifndef HADAMARD_HPP
#define HADAMARD_HPP

#include "matrix.hpp"
#include <cmath>

#ifndef Complex
#include <complex>
#define Complex std::complex<double>
#endif

class Hadamard : public Matrix
{
public:
    Hadamard() : Matrix{2, 2}
    {
        mtrx_data[0] = Complex{1 / sqrt(2), 0};
        mtrx_data[1] = Complex{1 / sqrt(2), 0};
        mtrx_data[2] = Complex{1 / sqrt(2), 0};
        mtrx_data[3] = Complex{-1 / sqrt(2), 0};
    }
    ~Hadamard() {}
};

#endif