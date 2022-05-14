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
        QuantumCircuit qc{3};
        qc.initialize(Complex{0, -sqrt(3) / 2},
            Complex{0.5, 0}, 0);
        qc.h(1);
        qc.x(2);
        qc.cx(0, 2);
        qc.cx(2, 1);
        qc.h(2);
        qc.measure_all();
    }

    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}