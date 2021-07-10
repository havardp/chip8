#pragma once
#include <SDL.h>

class Screen{
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	Screen(int window_scale);
	~Screen();

	void draw(const void* frame);
};