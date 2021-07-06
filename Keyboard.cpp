#include "Keyboard.h"

bool Keyboard::check_keydown(int polled_key)
{
	SDL_PumpEvents();
	const Uint8* kb = SDL_GetKeyboardState(NULL);
	return kb[keypadToScancode[polled_key]];
}

int Keyboard::find_any_keydown()
{
	SDL_PumpEvents();
	const Uint8* kb = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < 16; i++)
		if (kb[keypadToScancode[i]])
			return i;

	return -1;
}