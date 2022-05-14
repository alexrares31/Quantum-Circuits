#ifndef IDENTITY_HPP
#define IDENTITY_HPP

#include "matrix.hpp"

class Identity : public Matrix
{
public:
    Identity();
    Identity(int nqubits);
    ~Identity();
};

#endif