#ifndef HELPERS_H
#define HELPERS_H

#include <algorithm>

inline double random_double(double lower, double upper)
{
    if (lower > upper) std::swap(lower,upper);
    return (rand()/(static_cast<double>(RAND_MAX)+1.0))*(upper-lower)+lower;
}

template <typename T> int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

#endif // HELPERS_H
