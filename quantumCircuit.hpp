#ifndef QUANTUMCIRCUIT_HPP
#define QUANTUMCIRCUIT_HPP

#include "matrix.hpp"
#include "singleQubit.hpp"

class QuantumCircuit
{
private:
    int nqubits;
    size_t dimension;
    SingleQubit* qubits;
    Matrix state_vector;
    bool state_vector_saved;
    Matrix operator_mtrx;
    void save_state_vector();
public:
    QuantumCircuit();
    QuantumCircuit(int n);
    ~QuantumCircuit();
    void initialize(const Complex& c1,
        const Complex& c2, int n);
    void x(int n);
    void h(int n);
    void cx(int controlq, int targetq);
    Matrix get_state_vector();
    Matrix get_operator_mtrx();
    void measure_all(int precision=3);
};

#endif