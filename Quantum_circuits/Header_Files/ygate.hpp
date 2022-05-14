#ifndef YGATE_HPP
#define YGATE_HPP

#include "matrix.hpp"

#ifndef Complex
#include <complex>
#define Complex std::complex<double>
#endif

class YGate : public Matrix
{
public:
    YGate() : Matrix{2, 2}
    {
        mtrx_data[0] = Complex{0, 0};
        mtrx_data[1] = Complex{0, -1};
        mtrx_data[2] = Complex{0, 1};
        mtrx_data[3] = Complex{0, 0};
    }
    ~YGate() {}
};

#endif