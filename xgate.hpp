#ifndef XGATE_HPP
#define XGATE_HPP

#include "matrix.hpp"

class XGate : public Matrix
{
public:
    XGate() : Matrix{2, 2}
    {
        mtrx_data[0] = Complex{0, 0};
        mtrx_data[1] = Complex{1, 0};
        mtrx_data[2] = Complex{1, 0};
        mtrx_data[3] = Complex{0, 0};       
    }
    ~XGate() {}
};

#endif