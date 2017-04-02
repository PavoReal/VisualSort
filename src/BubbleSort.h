#pragma once

#include "ISort.hpp"
#include "Elements.hpp"

class BubbleSort : public ISort
{
public:
    BubbleSort();

    void
    Run(Elements& elements, size_t left, size_t right);
};
