#pragma once
#include <SDL.h>

class Screen{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
public:
	Screen(int window_scale);
	~Screen();
	void draw(const void* frame);
};