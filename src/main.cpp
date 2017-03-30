#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define ELEMENT_COUNT (50)

static SDL_Window* window;
static SDL_Renderer* renderer;
static int windowWidth, windowHeight;
static TTF_Font* font;

template <typename T> constexpr static inline
T Map(T x, T minIn, T maxIn, T minOut, T maxOut)
{
    return (x - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
}

static inline
int Round(float value)
{
    int result = static_cast<int>(roundf(value));

    return result;
}

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

static
void Render(Elements& elements, const char* name)
{
    auto* nameSurface = TTF_RenderText_Solid(font, name, { 255, 255, 255, 255 });
    auto  nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);

    SDL_FreeSurface(nameSurface);

    SDL_Rect r;
    r.x = r.y = 10;

    SDL_QueryTexture(nameTexture, 0, 0, &r.w, &r.h);

    const auto ELEMENT_WIDTH = (windowWidth / ELEMENT_COUNT);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    for (size_t i = 0; i < elements.size(); ++i)
    {
        SDL_Rect rect;
        rect.x = i * ELEMENT_WIDTH;
        rect.y = windowHeight;
        rect.w = ELEMENT_WIDTH;
        rect.h = Round(-Map(elements[i].val, 0.0f, static_cast<float>(elements.size()), 100.0f,
                            static_cast<float>(windowHeight)));

        SDL_SetRenderDrawColor(renderer, elements[i].r, elements[i].g, elements[i].b, 0xff);
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderCopy(renderer, nameTexture, NULL, &r);
    SDL_RenderPresent(renderer);
}

static
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

class Sort
{
public:
    Sort() { _name = ""; }
    Sort(std::string name_) : _name(name_) {}

    virtual void
    Run(Elements&, size_t, size_t) = 0; 

    inline void 
    SetName(std::string s) { _name = s; }
        
    inline std::string 
    GetName() { return _name; }

protected:
    std::string _name;
};

class InsertionSort : public Sort
{
public:
    InsertionSort() { _name = "Insertion Sort"; }

    void
    Run(Elements& elements, size_t, size_t)
    {
        Render(elements, _name.c_str());

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

                Render(elements, _name.c_str());
                Update();
                SDL_Delay(25);
                Update();
            }
        }
    }
};

class SelectionSort : public Sort
{
public:
    SelectionSort() { _name = "Selection Sort"; }

    void
    Run(Elements& elements, size_t, size_t)
    {
        Render(elements, _name.c_str());

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

                Render(elements, _name.c_str());

                elements[j].r = oldR;
                elements[j].g = oldG;
                elements[j].b = oldB;

                Update();
                SDL_Delay(35);
                Update();
            }

            std::swap(elements[i], elements[minIndex]);
        }
    };
};

class BubbleSort : public Sort
{
public:
    BubbleSort() { _name = "Bubble Sort"; }

    void
    Run(Elements& elements, size_t left, size_t right)
    {
        Render(elements, _name.c_str());

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

                    Render(elements, _name.c_str());
                    Update();
                }
            }
       }    
    };
};

class QuickSort : public Sort
{
public:
    QuickSort() { _name = "Quick Sort"; }

    void
    Run(Elements& elements, size_t left, size_t right)
    {    
        auto i = left;
        auto j = right;
        auto pivot = elements[(left + right) / 2].val;

        Render(elements, _name.c_str());
        SDL_Delay(20);

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

               
            Render(elements, _name.c_str());
            SDL_Delay(60);
            Update();
        }

        if (left < j)
        {
            Run(elements, left, j);
        }

        if (i < right)
        {
            Run(elements, i, right);
        }
    };
};

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    font = TTF_OpenFont("./OpenSans-Regular.ttf", 32);

    if (!font)
    {
        std::cerr << "Could not load font!" << std::endl;
    }

    window = SDL_CreateWindow("Visual Sort", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080,
                              SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Elements elements = {};

    std::array<Sort*, 4> sortingFunctions;
    sortingFunctions[0] = new QuickSort();
    sortingFunctions[1] = new BubbleSort();
    sortingFunctions[2] = new SelectionSort();
    sortingFunctions[3] = new InsertionSort();

    for (;;)
    {
        for (auto& func : sortingFunctions)
        {    
            std::srand(static_cast<unsigned>(time(0)));

            for (size_t i = 0; i < elements.size(); ++i)
            {
                elements[i].r = 0xff;
                elements[i].g = 0xff;
                elements[i].b = 0xff;

                auto val = static_cast<float>(std::rand() % ELEMENT_COUNT);

                for (size_t j = 0; j < i; ++j)
                {
                    if (val == elements[j].val)
                    {
                        val = static_cast<float>(std::rand() % ELEMENT_COUNT);
                        j = 0;
                    }
                }

                elements[i].val = val;
            }

            func->Run(elements, 0, elements.size());

            Update();
            SDL_Delay(1000);
            Update();
        }
    }
}
