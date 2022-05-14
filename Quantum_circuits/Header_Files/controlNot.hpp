#ifndef CONTROLNOT_HPP
#define CONTROLNOT_HPP

#include "matrix.hpp"

class ControlNot : public Matrix
{
public:
    ControlNot();
    ControlNot(const int& nqubits,
        const int& controlq, const int& targetq);
    ~ControlNot();
};

#endif