#pragma once

#include "ISort.hpp"
#include "Elements.hpp"

class SelectionSort : public ISort
{
public:
    SelectionSort(); 

    void
    Run(Elements& elements, size_t, size_t);
};

