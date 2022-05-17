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
        QuantumCircuit qc{3};   // Maximum 8 qubits
        qc.initialize(Complex{0, -std::sqrt(3) / 2},
            Complex{0.5, 0},
            0);
        qc.initialize(Complex{0, std::sqrt(2) / 2},
            Complex{std::sqrt(2) / 2, 0},
            1);
        qc.y(0);
        qc.h(1);
        qc.x(2);
        qc.z(2);
        qc.cx(0, 2);
        qc.h(2);
        qc.t(2);
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