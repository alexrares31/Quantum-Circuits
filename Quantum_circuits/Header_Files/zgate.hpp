#ifndef ZGATE_HPP
#define ZGATE_HPP

#include "matrix.hpp"

#ifndef Complex
#include <complex>
#define Complex std::complex<double>
#endif

class ZGate : public Matrix
{
public:
    ZGate() : Matrix{2, 2}
    {
        mtrx_data[0] = Complex{1, 0};
        mtrx_data[1] = Complex{0, 0};
        mtrx_data[2] = Complex{0, 0};
        mtrx_data[3] = Complex{-1, 0};
    }
    ~ZGate() {}
};

#endif