#include <array>
#include <SDL2/SDL.h>

#define rand() (arc4random() % ((unsigned)RAND_MAX + 1))

using uint = unsigned int;
using uint8 = uint8_t;
using uint32 = uint32_t;

struct element;
void Render(const element* e);

SDL_Window* window;
SDL_Renderer* renderer;

struct element
{
    uint32 value;
    uint8 r, g, b;

    inline
    element() : value(0), r(0), g(0), b(0) {}


    friend inline
    bool operator > (const element& a, const element& b)
    {
        bool result;

        result = a.value > b.value;

        Render(&a);

        return result;
    }

    friend inline
    bool operator < (const element& a, const element& b)
    {
        bool result;

        result = a.value < b.value;

        Render(&a);

        return result;
    }
};

void Render(element* e, int count)
{
    constexpr auto ELEMENT_HEIGHT = 400;
    constexpr auto ELEMENT_WIDTH = 800 / 100;

    SDL_Rect rects[count];
    for (auto i = 0; i < count; ++i)
    {
        rects[i].h = ELEMENT_HEIGHT;
        rects[i].w = ELEMENT_WIDTH;
        rects[i].x = ;
        rects[i].y = ;
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderDrawRects(renderer, rects, count);
    SDL_RenderPresent(renderer);

    SDL_Delay(250);
}

void QuickSort(element* elements, int elementsCount, int left, int right)
{
    auto i = left;
    auto j = right;
    auto pivot = elements[(left + right) / 2].value;
    element tmp;

    Render(elements, elementsCount);

    /* partition */
    while (i <= j)
    {
        while (elements[i].value < pivot)
        {
            i++;
        }

        while (elements[j].value > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            tmp = elements[i];
            elements[i] = elements[j];
            elements[j] = tmp;

            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        QuickSort(elements, elementsCount, left, j);
    if (i < right)
        QuickSort(elements, elementsCount, i, right);
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Visual Sort", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    std::array<element, 100> elements = {};

    int id = 0;
    for (auto& i : elements)
    {
        i = {};
        i.r = static_cast<uint8>(rand() % 255);
        i.g = static_cast<uint8>(rand() % 255);
        i.b = static_cast<uint8>(rand() % 255);
        i.value = arc4random();

        id += 2;
    }

    SDL_RenderClear(renderer);

    QuickSort(elements.__elems_, static_cast<int>(elements.size()), 0, static_cast<int>(elements.size()));

    return 0;
}
