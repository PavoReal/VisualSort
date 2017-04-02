#pragma once

#include "ISort.hpp"
#include "Elements.hpp"

class QuickSort : public ISort
{
public:
    QuickSort();

    void
    Run(Elements& elements, size_t left, size_t right);
};

