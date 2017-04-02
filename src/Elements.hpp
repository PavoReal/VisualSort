#pragma once

#include <array>

struct Element
{
    float val;
    int r, g, b;

    friend inline bool 
    operator <(const Element& lhs, const Element& rhs)
    {
        return lhs.val < rhs.val;
    }

    friend inline bool
    operator >(const Element& lhs, const Element& rhs)
    {
       return lhs.val > rhs.val;
    }
};

using Elements = std::array<Element, ELEMENT_COUNT>;

