#include "Keyboard.h"

void Keyboard::update_keyboard_state(bool keyboard_state[], bool& quit_flag, bool& mute_flag)
{
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT)
		quit_flag = true;

	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_m)
		mute_flag = !mute_flag;

	const Uint8* kb = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < 16; i++)
		keyboard_state[i] = kb[keypadToScancode[i]];

}