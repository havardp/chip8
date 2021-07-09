#pragma once
#include <SDL.h>

// Credit to: https://github.com/tomdaley92/kiwi-8

#define FREQUENCY 48000
#define TONE 440
#define AMPLITUDE 7
#define BIAS 127
#define SAMPLES_PER_FRAME ((FREQUENCY / 60) * 3)

class Audio2 {
private:
    SDL_AudioDeviceID device;
    unsigned char* audio_buffer;

    double wave_position;
    double wave_increment;

public:
    Audio2();
    ~Audio2();
    void Beep();
};