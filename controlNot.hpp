#ifndef CONTROLNOT_HPP
#define CONTROLNOT_HPP

#include "matrix.hpp"

#ifndef MAXQUBITS
#define MAXQUBITS 16
#endif

class ControlNot : public Matrix
{
public:
    ControlNot();
    ControlNot(const int& nqubits,
        const int& controlq, const int& targetq);
    ~ControlNot();
};

#endif