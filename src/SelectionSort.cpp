#include "SelectionSort.h"
#include <SDL.h>
#include "Renderer.h"

SelectionSort::SelectionSort()
{
    _name = "Selection Sort"; 
}

void
SelectionSort::Run(Elements& elements, size_t, size_t)
{
    UpdateAndRender(elements, _name, 25);

    for (size_t i = 0; i < elements.size(); ++i)
    {
        for (size_t j = 0; j < elements.size(); ++j)
        {
            elements[j].r = 0xff;
            elements[j].g = 0xff;
            elements[j].b = 0xff;
        }

        auto minIndex = i;

        elements[i].r = 0xee;
        elements[i].g = 0x00;
        elements[i].b = 0x00;

        for (auto j = i; j < elements.size(); ++j)
        {
            auto oldR = elements[j].r;
            auto oldG = elements[j].g;
            auto oldB = elements[j].b;

            elements[j].r = 0x00;
            elements[j].g = 0x00;
            elements[j].b = 0xee;

            if (elements[j] < elements[minIndex])
            {
                elements[minIndex].r = 0xff;
                elements[minIndex].g = 0xff; 
                elements[minIndex].b = 0xff;

                minIndex = j;

                oldR = 0xee;
                oldG = 0;
                oldB = 0;

                elements[minIndex].r = 0xee;
                elements[minIndex].g = 0x00; 
                elements[minIndex].b = 0x00;
            }

            UpdateAndRender(elements, _name, 25);

            elements[j].r = oldR;
            elements[j].g = oldG;
            elements[j].b = oldB;
        }

        std::swap(elements[i], elements[minIndex]);
    }
}

