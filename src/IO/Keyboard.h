#pragma once
#include <unordered_map>
#include <sdl.h>

class Keyboard
{
private:
	SDL_Event e;
	std::unordered_map<int, int> keypadToScancode{
		{1, SDL_SCANCODE_1},
		{2, SDL_SCANCODE_2},
		{3, SDL_SCANCODE_3},
		{0xC, SDL_SCANCODE_4},
		{4, SDL_SCANCODE_Q},
		{5, SDL_SCANCODE_W},
		{6, SDL_SCANCODE_E},
		{0xD, SDL_SCANCODE_R},
		{7, SDL_SCANCODE_A},
		{8, SDL_SCANCODE_S},
		{9, SDL_SCANCODE_D},
		{0xE, SDL_SCANCODE_F},
		{0xA, SDL_SCANCODE_Z},
		{0, SDL_SCANCODE_X},
		{0xB, SDL_SCANCODE_C},
		{0xF, SDL_SCANCODE_V},
	};

public:
	void update_keyboard_state(bool keyboard_state[], bool& quit_flag, bool& mute_flag, bool& pause_flag);
};