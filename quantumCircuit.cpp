#include "quantumCircuit.hpp"
#include "power.hpp"
#include "singleQubit.hpp"
#include "identity.hpp"
#include "xgate.hpp"
#include "hadamard.hpp"
#include "controlNot.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>

#ifndef Complex
#include <complex>
#define Complex std::complex<double>
#endif

#ifndef MAXQUBITS
#define MAXQUBITS 8
#endif

QuantumCircuit::QuantumCircuit()
{
    throw std::invalid_argument(
        "Constructor expects valid argument.");
}

QuantumCircuit::QuantumCircuit(int n) :
    nqubits{n},
    dimension{power(2, nqubits)},
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
/*
    Initializes the individual single qubit n as
    following: |qn> = c1|0> + c2|1>
    Note that if the state vector has already been 
    built, then an error is thrown. This prevents
    initializing single qubit states after they were
    entangled.
*/
{
    if (n < 0 || n >= nqubits)
        throw std::out_of_range(
            "Out of range error.");
    else
        if (state_vector_saved == true)
            throw std::logic_error(
                "Logic error: Single qubits cannot "
                "be initialized after the state "
                "vector is built.");
        else
            qubits[n] = SingleQubit(c1, c2);
}

void QuantumCircuit::save_state_vector()
/*
    Builds the 2^nqubits state vector. The function
    is called before applying a quantum gate.
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
/*
    Applies an X gate on qubit n.
*/
{
    if (n < 0 || n >= nqubits) {
        throw std::out_of_range(
            "Out of range error.");
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
/*
    Applies a Hadamard gate on qubit n.
*/
{
    if (n < 0 || n >= nqubits) {
        throw std::out_of_range(
            "Out of range error.");
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
/*
    Applies a CNOT gate on the specified control
    and target qubits.
*/
{
    if (controlq < 0 || controlq >= nqubits ||
        targetq < 0 || targetq >= nqubits) {
        throw std::out_of_range(
            "Out of range error.");
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

void QuantumCircuit::measure_all(int precision)
/*
    Computes and prints the measurement probabilities 
    for the given precision. The function also
    collapses the state vector onto |00...00>
*/
{
    if (state_vector_saved == false)
        save_state_vector();
    for (size_t i{0}; i < dimension; i++) {
        double probability, threshold;
        probability = std::pow(
            std::abs(state_vector(i, 0)), 2);
        threshold = std::pow(10, -precision);
        if (probability > threshold) {
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
        if (i == 0)
            state_vector(i, 0) = Complex{1, 0};
        else
            state_vector(i, 0) = Complex{0, 0};
    }
}