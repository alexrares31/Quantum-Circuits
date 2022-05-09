#ifndef QUANTUMCIRCUIT_HPP
#define QUANTUMCIRCUIT_HPP

#include "matrix.hpp"
#include "singleQubit.hpp"

#ifndef MAXQUBITS
#define MAXQUBITS 16
#endif

class QuantumCircuit
{
    // friend entangle_qubits(int n, ); ...
private:
    int nqubits;
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
    void x(int n);  // applies an x gate on qubit qn
    void h(int n);
    void cx(int controlq, int targetq);
    Matrix get_state_vector();
    Matrix get_operator_mtrx();
    void measure_all(double error=1e-6,
        int precision=3);
};

#endif