#include "power.hpp"

size_t power(const int& base, const int& exp)
{
    size_t result{1};
    for (int i{0}; i < exp; i++)
        result *= base;

    return result;    
}