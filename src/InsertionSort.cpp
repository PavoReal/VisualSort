#include "InsertionSort.h"
#include <SDL.h>
#include "Renderer.h"

InsertionSort::InsertionSort()
{
    _name = "Insertion Sort";
}

void
InsertionSort::Run(Elements& elements, size_t, size_t)
{
    UpdateAndRender(elements, _name, 35);

    size_t sortedIndex = 0;

    for (size_t i = sortedIndex; i < elements.size(); ++i)
    {
        auto j = i;

        while ((j > 0) && (elements[j] < elements[j - 1]))
        {
            for (auto& e : elements)
            {
                e.r = 0xff;
                e.g = 0xff;
                e.b = 0xff;
            }

            std::swap(elements[j], elements[j - 1]);
            --j;

            elements[j].r = 0xee;
            elements[j].g = 0x00;
            elements[j].b = 0x00;

            UpdateAndRender(elements, _name, 35);
        }
    }
}

