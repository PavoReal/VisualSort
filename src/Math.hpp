#pragma once

#include "cmath"
    
template <typename T> constexpr inline
T Map(T x, T minIn, T maxIn, T minOut, T maxOut)
{
    return (x - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
}

inline
int Round(float value)
{
    int result = static_cast<int>(roundf(value));

    return result;
}

