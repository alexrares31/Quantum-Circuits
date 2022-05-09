#include "quantumCircuit.hpp"
#include "power.hpp"
#include "singleQubit.hpp"
#include "identity.hpp"
#include "xgate.hpp"
#include "hadamard.hpp"
#include "controlNot.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>

#ifndef Complex
#include <complex>
#define Complex std::complex<double>
#endif

QuantumCircuit::QuantumCircuit()
{
    throw "Empty circuit.";
}

QuantumCircuit::QuantumCircuit(int n) :
    nqubits{n},
    qubits{new SingleQubit[n]},
    state_vector{Matrix {power(2, n), 1}},
    state_vector_saved{false},
    operator_mtrx{Identity{n}} {}

QuantumCircuit::~QuantumCircuit()
{
    if (state_vector_saved == false)
        delete[] qubits;
}

void QuantumCircuit::initialize(
    const Complex& c1, const Complex& c2, int n)
{
    if (n < 0 || n >= nqubits)
        throw "Out of range error.";
    else
        if (state_vector_saved == true)
            throw "State vector already saved.";
        else
            qubits[n] = SingleQubit(c1, c2);
}

void QuantumCircuit::save_state_vector()
/*
    Builds the 2^nqubits state vector. The function
    should be called before applying a quantum
    gate.
*/
{
    if (state_vector_saved == false) {
        Matrix q;
        for (int i{0}; i < nqubits; i++) {
            if (i == 0)
                q = qubits[0];
            else
                q = kron(qubits[i], q);
        }
        state_vector = q;
        state_vector_saved = true;
        delete[] qubits;
    }
}

void QuantumCircuit::x(int n)
{
    if (n < 0 || n >= nqubits) {
        throw "Out of range error.";
    } else {
        if (state_vector_saved == false)
            save_state_vector();
        Identity i_gate;
        XGate x_gate;
        Matrix m; 
        for (int i{0}; i < nqubits; i++)
            if (i == 0)
                if (n == 0)
                    m = x_gate;
                else
                    m = i_gate;
            else
                if (i == n)
                    m = kron(x_gate, m);
                else
                    m = kron(i_gate, m);
        state_vector = m * state_vector;
        operator_mtrx = m * operator_mtrx;
    }
}

void QuantumCircuit::h(int n)
{
    if (n < 0 || n >= nqubits) {
        throw "Out of range error.";
    } else {
        if (state_vector_saved == false)
            save_state_vector();
        Identity i_gate;
        Hadamard h_gate;
        Matrix m; 
        for (int i{0}; i < nqubits; i++)
            if (i == 0)
                if (n == 0)
                    m = h_gate;
                else
                    m = i_gate;
            else
                if (i == n)
                    m = kron(h_gate, m);
                else
                    m = kron(i_gate, m);
        state_vector = m * state_vector;
        operator_mtrx = m * operator_mtrx;
    }
}

void QuantumCircuit::cx(int controlq, int targetq)
{
    if (controlq < 0 || controlq >= nqubits ||
        targetq < 0 || targetq >= nqubits) {
        throw "Out of range error.";
    } else {
        if (state_vector_saved == false)
            save_state_vector();
        ControlNot cx_gate{nqubits,
        controlq, targetq};
        state_vector = cx_gate * state_vector;
        operator_mtrx = cx_gate * operator_mtrx;
    }
}

Matrix QuantumCircuit::get_state_vector()
{
    if (state_vector_saved == false)
        save_state_vector();

    return state_vector;
}

Matrix QuantumCircuit::get_operator_mtrx()
{
    return operator_mtrx;
}

void QuantumCircuit::measure_all(
    double error, int precision)
{
    if (state_vector_saved == false)
        save_state_vector();
    size_t dimension{power(2, nqubits)};
    for (size_t i{0}; i < dimension; i++) {
        double probability;
        probability = std::abs(state_vector(i, 0));
        if (probability > error) {
            std::string bin_string;
            bin_string = std::bitset<MAXQUBITS>(i)
                .to_string()
                .substr(MAXQUBITS-nqubits);
            std::cout << "Probability of |"
                << bin_string
                << "> is: "
                << std::setprecision(precision)
                << probability
                << '\n';
        }
    }
}