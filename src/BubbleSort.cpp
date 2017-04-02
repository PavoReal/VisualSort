#include "BubbleSort.h"
#include <SDL.h>
#include "Renderer.h"

BubbleSort::BubbleSort()
{
    _name = "Bubble Sort";
}

void
BubbleSort::Run(Elements& elements, size_t left, size_t right)
{
    UpdateAndRender(elements, _name, 20);

    for (size_t i = left; i < right - 1; ++i)
    {
        for (size_t j = left; j < elements.size() - i - 1; ++j)
        {
            if (elements[j].val > elements[j + 1].val)
            {
                std::swap(elements[j].val, elements[j + 1].val);

                for (Element& e : elements)
                {
                    e.r = 0xff;
                    e.g = 0xff;
                    e.b = 0xff;
                }

                elements[j].r = 0x00;
                elements[j].g = 0xee;
                elements[j].b = 0x00;

                UpdateAndRender(elements, _name, 20);
            }
        }
    }    
}

