#include "power.hpp"

size_t power(const int& base, const int& exp)
/*
    Equivalent to the the std::pow function, 
    but returns size_t types.
*/
{
    size_t result{1};
    for (int i{0}; i < exp; i++)
        result *= base;

    return result;    
}