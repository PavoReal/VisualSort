#include <array>
#include <random>
#include <algorithm>
#include <SDL2/SDL.h>

using uint = unsigned int;
using uint8 = uint8_t;
using uint32 = uint32_t;

SDL_Window* window;
SDL_Renderer* renderer;

template <typename T> constexpr inline
T Map(T x, T minIn, T maxIn, T minOut, T maxOut)
{
    return (x - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
}

void Render(uint32* elements, int count)
{
    constexpr auto ELEMENT_WIDTH = (800 / 100) - 1;

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    for (auto i = 0; i < count; ++i)
    {
        SDL_Rect rect = {};
        rect.x = i * ELEMENT_WIDTH;
        rect.y = 0;
        rect.w = ELEMENT_WIDTH;
        rect.h = Map(elements[i], 0U, 100U, 100U, 500U);

        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(50);
}

void Update()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            exit(0);
        }
    }
}

void QuickSort(uint32* elements, int elementsCount, int left, int right)
{
    auto i = left;
    auto j = right;
    auto pivot = elements[(left + right) / 2];
    uint32 tmp;

    Render(elements, elementsCount);

    /* partition */
    while (i <= j)
    {
        while (elements[i] < pivot)
        {
            i++;
        }

        while (elements[j] > pivot)
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

        Render(elements, elementsCount);
        Update();
    };

    if (left < j)
    {
        QuickSort(elements, elementsCount, left, j);
    }

    if (i < right)
    {
        QuickSort(elements, elementsCount, i, right);
    }
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Visual Sort", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    std::array<uint32, 100> elements = {};

    std::srand(static_cast<unsigned>(std::time(0)));
    std::generate(elements.begin(), elements.end(), []() { return std::rand() % 100; });

    QuickSort(elements.__elems_, static_cast<int>(elements.size()), 0, static_cast<int>(elements.size()));

    for (;;)
    {
        Update();
    }

    return 0;
}
