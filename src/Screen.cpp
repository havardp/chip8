#include "Screen.h"

Screen::Screen(int window_scale)
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Chip8 emulator", 100, 100, 64 * window_scale, 32 * window_scale, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_STREAMING, 64, 32);
}

Screen::~Screen()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Screen::draw(const void* frame)
{
	SDL_UpdateTexture(texture, nullptr, frame, 64);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}