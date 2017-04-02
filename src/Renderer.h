#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Elements.hpp"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int windowWidth, windowHeight;
extern TTF_Font* font;

extern void
UpdateAndRender(const Elements& elements, const std::string& name, size_t delay);

