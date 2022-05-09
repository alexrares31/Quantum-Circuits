#ifndef SINGLEQUBIT_HPP
#define SINGLEQUBIT_HPP

#include "matrix.hpp"

class SingleQubit : public Matrix
{
public:
    SingleQubit();
    SingleQubit(const Complex& c1,
        const Complex& c2);
    ~SingleQubit();
    SingleQubit& operator=(const Matrix& other);
};

#endif