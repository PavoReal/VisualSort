#include <array>
#include <random>
#include <SDL2/SDL.h>

#define ELEMENT_COUNT (100)

SDL_Window* window;
SDL_Renderer* renderer;
int windowWidth, windowHeight;

template <typename T> constexpr inline
T Map(T x, T minIn, T maxIn, T minOut, T maxOut)
{
    return (x - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
}

inline
int Round(float value)
{
    int result = static_cast<int>(roundf(value));

    return result;
}

void Render(float* elements, int count, int left, int right, int pivot)
{
    const auto ELEMENT_WIDTH = (windowWidth / ELEMENT_COUNT);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    for (auto i = 0; i < count; ++i)
    {
        SDL_Rect rect = {};
        rect.x = i * ELEMENT_WIDTH;
        rect.y = windowHeight;
        rect.w = ELEMENT_WIDTH;
        rect.h = Round(-Map(elements[i], 0.0f, static_cast<float>(ELEMENT_COUNT), 100.0f, static_cast<float>(windowHeight)));

        if (i == left || i == right)
        {
            SDL_SetRenderDrawColor(renderer, 0x11 , 0x11, 0xaa, 0xff);
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        }
        else if (i == pivot)
        {
            SDL_SetRenderDrawColor(renderer, 0x11 , 0xaa, 0x11, 0xff);
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        }
        else
        {
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(40);
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

void QuickSort(float* elements, int elementsCount, int left, int right)
{
    auto i = left;
    auto j = right;
    auto pivot = elements[(left + right) / 2];
    float tmp;

    Render(elements, elementsCount, left, right, static_cast<int>(pivot));

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

        Render(elements, elementsCount, left, right, pivot);
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

    window = SDL_CreateWindow("Visual Sort", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    std::array<float, ELEMENT_COUNT> elements = {};

    std::srand(static_cast<unsigned>(std::time(0)));

    for (size_t i = 0; i < elements.size(); ++i)
    {
        auto val = static_cast<float>(std::rand() % ELEMENT_COUNT);

        for (size_t j = 0; j < i; ++j)
        {
            if (val == elements[j])
            {
                val = static_cast<float>(std::rand() % ELEMENT_COUNT);
                j = 0;
            }
        }

        elements[i] = val;
    }

    QuickSort(elements.__elems_, static_cast<int>(elements.size()), 0, static_cast<int>(elements.size()));

    for (;;)
    {
        Update();
    }
}
