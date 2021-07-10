#include "Audio.h"

#define FREQUENCY 48000
#define TONE 440
#define SAMPLES_PER_FRAME ((FREQUENCY / 60) * 3)
#define AMPLITUDE 7
#define BIAS 127

Audio::Audio() : 
    wave_position{ 0 }, 
    wave_increment{ ((double)TONE * (2.0 * M_PI)) / (double)FREQUENCY } 
{
    if (SDL_Init(SDL_INIT_AUDIO) != 0) SDL_Log("Failed to initialize SDL: %s", SDL_GetError());

    SDL_AudioSpec audiospec;
    audiospec.freq = FREQUENCY;
    audiospec.format = AUDIO_U8;
    audiospec.channels = 1;
    audiospec.samples = 2048;
    audiospec.callback = NULL;
    audiospec.userdata = NULL;

    // open default audio device
    device = SDL_OpenAudioDevice(NULL, 0, &audiospec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    // ~.5 seconds worth of audio
    audio_buffer = (unsigned char*)malloc(SAMPLES_PER_FRAME * 30);

    // start playing audio 
    SDL_PauseAudioDevice(device, 0);
}

Audio::~Audio() 
{
    SDL_PauseAudioDevice(device, 1);
    if (device) SDL_CloseAudioDevice(device);
    free(audio_buffer);
}

void Audio::Beep() 
{
    if (SDL_GetQueuedAudioSize(device) < (SAMPLES_PER_FRAME * 2)) 
    {
        // Fill audio buffer with sine wave in range 120-134
        for (int i = 0; i < SAMPLES_PER_FRAME; i++) 
        {
            audio_buffer[i] = (unsigned char)((AMPLITUDE * sin(wave_position)) + BIAS);
            wave_position += wave_increment;
        }

        // Queue the audio
        SDL_QueueAudio(device, audio_buffer, SAMPLES_PER_FRAME);
    }
}