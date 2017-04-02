#include "QuickSort.h"
#include <SDL.h>
#include "Renderer.h"

QuickSort::QuickSort() { _name = "Quick Sort"; }

void
QuickSort::Run(Elements& elements, size_t left, size_t right)
{    
    auto i = left;
    auto j = right;
    auto pivot = elements[(left + right) / 2].val;

    UpdateAndRender(elements, _name, 50);

    while (i <= j)
    {
        while (elements[i].val < pivot)
        {
            i++;
        }

        while (elements[j].val > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            std::swap(elements[i], elements[j]);

            i++;
            j--;
        }

        for (Element& e : elements)
        {
            e.r = 0xff;
            e.g = 0xff;
            e.b = 0xff;
        }

        if (left > 0 && left < elements.size())
        {
            elements[left].r = 0x00;
            elements[left].g = 0xee;
            elements[left].b = 0x00;
        }

        if (right > 0 && right < elements.size())
        {
            elements[right].r = 0x00;
            elements[right].g = 0xee;
            elements[right].b = 0x00;
        }

        if (pivot > 0 && pivot < elements.size())
        {
            elements[pivot].r = 0xee;
            elements[pivot].g = 0x00;
            elements[pivot].g = 0x00;
        }
       
        UpdateAndRender(elements, _name, 50);
    }

    if (left < j)
    {
        Run(elements, left, j);
    }

    if (i < right)
    {
        Run(elements, i, right);
    }
}

