#pragma once
#include <SDL.h>
#include <SDL_audio.h>

class Audio {
public:
	Audio();
	void play_sound_if_sound_timer_greater_than_zero(uint8_t sound_timer);
private:
	void play();
	void pause();
};