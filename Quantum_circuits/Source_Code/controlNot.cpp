#include "controlNot.hpp"
#include "power.hpp"
#include <bitset>
#include <stdexcept>

#ifndef Complex
#include <complex>
#define Complex std::complex<double>
#endif

#ifndef MAXQUBITS
#define MAXQUBITS 8
#endif

ControlNot::ControlNot()
{
    throw std::invalid_argument(
        "Constructor expects valid argument.");
}

ControlNot::ControlNot(const int& nqubits,
    const int& controlq, const int& targetq) : 
    Matrix{power(2, nqubits), power(2, nqubits)}
{
    if (controlq < 0 || controlq >= nqubits
    || targetq < 0 || targetq >= nqubits
    || controlq == targetq) {
        throw std::out_of_range(
            "Out of range error.");
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