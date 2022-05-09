#include "identity.hpp"
#include "power.hpp"

#ifndef Complex
#include <complex>
#define Complex std::complex<double>
#endif

Identity::Identity() : Matrix{2, 2}
{
    mtrx_data[0] = Complex{1, 0};
    mtrx_data[1] = Complex{0, 0};
    mtrx_data[2] = Complex{0, 0};
    mtrx_data[3] = Complex{1, 0};
}

Identity::Identity(int nqubits) :
    Matrix{power(2, nqubits), power(2, nqubits)}
{
    size_t dim{power(2, nqubits)};
    for (size_t i{0}; i < dim; i++)
        for (size_t j{0}; j < dim; j++)
            if (i == j)
                mtrx_data[index(i, j)] =
                    Complex{1, 0};
            else
                mtrx_data[index(i, j)] =
                    Complex{0, 0};
}

Identity::~Identity() {}