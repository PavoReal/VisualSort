#include "Renderer.h"
#include "Math.hpp"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
int windowWidth = 0;
int windowHeight = 0;
TTF_Font* font = nullptr;

INTERNAL void 
RenderElements(const Elements& elements)
{
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
}   

INTERNAL void 
RenderName(const std::string& name)
{
    auto* nameSurface = TTF_RenderText_Blended(font, name.c_str(), { 255, 255, 255, 255 });
    auto  nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);

    SDL_FreeSurface(nameSurface);

    SDL_Rect r;
    r.x = 15;
    r.y = 10;

    SDL_QueryTexture(nameTexture, 0, 0, &r.w, &r.h);
    SDL_RenderCopy(renderer, nameTexture, NULL, &r);
}

INTERNAL void
Update()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_QUIT:
                exit(0);
                break;

            case SDL_WINDOWEVENT:
                switch (e.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                        windowWidth = e.window.data1;
                        windowHeight = e.window.data2;

                        break;
                }

                break;
        }
    }
}

void
UpdateAndRender(const Elements& elements, const std::string& name, size_t delay)
{
    Update();

    RenderElements(elements);
    RenderName(name);

    SDL_RenderPresent(renderer);

    SDL_Delay(delay); 

    Update();
}

