#ifndef TGATE_HPP
#define TGATE_HPP

#include "matrix.hpp"
#include <cmath>

#ifndef Complex
#include <complex>
#define Complex std::complex<double>
#endif

class TGate : public Matrix
{
public:
    TGate() : Matrix{2, 2}
    {
        mtrx_data[0] = Complex{1, 0};
        mtrx_data[1] = Complex{0, 0};
        mtrx_data[2] = Complex{0, 0};
        mtrx_data[3] = Complex{std::sqrt(2.) / 2.,
            std::sqrt(2.) / 2.};
    }
    ~TGate() {};
};

#endif