#include "controlNot.hpp"
#include "power.hpp"
#include <bitset>

#ifndef Complex
#include <complex>
#define Complex std::complex<double>
#endif

ControlNot::ControlNot() : Matrix{4, 4}
{
    mtrx_data[index(0, 0)] = Complex{1, 0};
    mtrx_data[index(1, 3)] = Complex{1, 0};
    mtrx_data[index(2, 2)] = Complex{1, 0};
    mtrx_data[index(3, 1)] = Complex{1, 0};
}

ControlNot::ControlNot(const int& nqubits,
    const int& controlq, const int& targetq) : 
    Matrix{power(2, nqubits), power(2, nqubits)}
{
    if (controlq < 0 || controlq >= nqubits
    || targetq < 0 || targetq >= nqubits
    || controlq == targetq) {
        throw "Out of range error.";
    } else {
        std::bitset<MAXQUBITS> ket;
        std::bitset<MAXQUBITS> bra;
        for (size_t i {0}; i < rows; i++) {
            for (size_t j {0}; j < cols; j++) {
                ket = std::bitset<MAXQUBITS>(j);
                bra = std::bitset<MAXQUBITS>(i);
                if (ket[controlq] == 1)
                    ket.flip(targetq);
                if (ket == bra)
                    mtrx_data[index(i, j)] = 1;
                else
                    mtrx_data[index(i, j)] = 0;
            }
        }
    }
}

ControlNot::~ControlNot() {}