#include "Audio.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
int _ = _putenv("SDL_AUDIODRIVER=DirectSound");
#endif

// Credit to: https://stackoverflow.com/questions/10110905/simple-sound-wave-generator-with-sdl-in-c/45002609#45002609

const int AMPLITUDE = 28000;
const int SAMPLE_RATE = 44100;

void audio_callback(void* user_data, Uint8* raw_buffer, int bytes)
{
	Sint16* buffer = (Sint16*)raw_buffer;
	int length = bytes / 2; // 2 bytes per sample for AUDIO_S16SYS
	int& sample_nr(*(int*)user_data);

	for (int i = 0; i < length; i++, sample_nr++)
	{
		double time = (double)sample_nr / (double)SAMPLE_RATE;
		buffer[i] = (Sint16)(AMPLITUDE * sin(2.0f * M_PI * 441.0f * time)); // render 441 HZ sine wave
	}
}

Audio::Audio()
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0) SDL_Log("Failed to initialize SDL: %s", SDL_GetError());

	int sample_nr = 0;

	SDL_AudioSpec want;
	want.freq = SAMPLE_RATE; // number of samples per second
	want.format = AUDIO_S16SYS; // sample type (here: signed short i.e. 16 bit)
	want.channels = 1; // only one channel
	want.samples = 2048; // buffer-size
	want.callback = audio_callback; // function SDL calls periodically to refill the buffer
	want.userdata = &sample_nr; // counter, keeping track of current sample number

	SDL_AudioSpec have;
	if (SDL_OpenAudio(&want, &have) != 0) SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to open audio: %s", SDL_GetError());
	if (want.format != have.format) SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to get the desired AudioSpec");
}

#include <iostream>
void Audio::play_sound_if_sound_timer_greater_than_zero(bool sound)
{
	if (sound)
	{
		SDL_PauseAudio(0);
	}
	else SDL_PauseAudio(1);
	SDL_Delay(3);
	//SDL_PauseAudio(1);
	//SDL_Delay(10000);
	//SDL_PauseAudio(1);
	//if (sound_timer > 0)
	//{
	//	std::cout << "BEEP\n";
	//	play();
	//}
	//else
	//{
	//	std::cout << "nobeep\n";
	//	//pause();
	//}
}

void Audio::play()
{
	SDL_PauseAudio(0);
}

void Audio::pause()
{
	SDL_PauseAudio(1);
}