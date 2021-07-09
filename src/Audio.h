#pragma once
#include <SDL.h>

// Credit to: https://github.com/tomdaley92/kiwi-8

class Audio {
private:
    SDL_AudioDeviceID device;
    unsigned char* audio_buffer;

    double wave_position;
    double wave_increment;

public:
    Audio();
    ~Audio();
    void Beep();
};