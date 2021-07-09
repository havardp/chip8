#pragma once
#include <SDL.h>
#include <SDL_audio.h>

class Audio {
public:
	Audio();
	void play_sound_if_sound_timer_greater_than_zero(bool sound);
private:
	void play();
	void pause();
};