#pragma once

#include "ISort.hpp"
#include "Elements.hpp"

class InsertionSort : public ISort
{
public:
    InsertionSort();

    void
    Run(Elements& elements, size_t, size_t);
};
