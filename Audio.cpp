#include "Audio.h"

constexpr int FREQUENCY = 48000;
constexpr int TONE = 440;
constexpr int SAMPLES_PER_FRAME = (FREQUENCY / 60) * 3;

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
        // fill audio buffer with sine wave in range 120-134
        for (int i = 0; i < SAMPLES_PER_FRAME; i++) 
        {
            audio_buffer[i] = (unsigned char)((7 * sin(wave_position)) + 127);
            wave_position += wave_increment;
        }
        SDL_QueueAudio(device, audio_buffer, SAMPLES_PER_FRAME);
    }
}