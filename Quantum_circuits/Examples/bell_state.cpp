#include "quantumCircuit.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

#ifndef Complex
#include <complex>
#define Complex std::complex<double>
#endif

int main()
{
    try
    {
        QuantumCircuit qc{2};
        qc.h(0);
        qc.cx(0, 1);
        qc.measure_all();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}