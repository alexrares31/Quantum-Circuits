#ifndef IDENTITY_HPP
#define IDENTITY_HPP

#include "matrix.hpp"
#include <cmath>

class Identity : public Matrix
{
public:
    Identity() : Matrix{2, 2}
    {        
        mtrx_data[0] = Complex{1, 0};
        mtrx_data[1] = Complex{0, 0};
        mtrx_data[2] = Complex{0, 0};
        mtrx_data[3] = Complex{1, 0};
    }
    ~Identity() {}
};

#endif