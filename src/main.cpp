#include <iostream>
#include <array>
#include <string>
#include <random>
#include <limits>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Math.hpp"
#include "Elements.hpp"
#include "ISort.hpp"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "BubbleSort.h"
#include "QuickSort.h"

#include "audio.h"

INTERNAL void
GenerateElements(Elements& elements)
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
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
	initAudio();

    font = TTF_OpenFont("./OpenSans-Regular.ttf", 36);

    if (!font)
    {
        std::cerr << "Could not load font!" << std::endl;

		return 1;
    }

    window = SDL_CreateWindow("Visual Sort", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900,
                              SDL_WINDOW_RESIZABLE);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Elements elements;

    std::array<ISort*, 4> sortingFunctions;
    sortingFunctions[0] = new QuickSort();
    sortingFunctions[1] = new BubbleSort();
    sortingFunctions[2] = new SelectionSort();
    sortingFunctions[3] = new InsertionSort();

	playMusic("./BrokeForFree.wav", SDL_MIX_MAXVOLUME * 0.4);

    for (auto& sortingFunc : sortingFunctions)
    {    
        GenerateElements(elements);

		sortingFunc->Run(elements, 0, elements.size());

        SDL_Delay(1000);
    }
}

