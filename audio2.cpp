#include "audio2.h"

Audio2::Audio2() : 
    wave_position{ 0 }, 
    wave_increment{ ((double)TONE * (2.0 * M_PI)) / (double)FREQUENCY } 
{
    if (SDL_Init(SDL_INIT_AUDIO) != 0) SDL_Log("Failed to initialize SDL: %s", SDL_GetError()); // THIS IS THE DIFF THAT MAKES IT WORK
    SDL_AudioSpec audiospec;
    audiospec.freq = FREQUENCY;
    audiospec.format = AUDIO_U8; /* unsigned 8-bit data stream */
    audiospec.channels = 1; /* mono */
    audiospec.samples = 2048; /* must be a power of 2 */
    audiospec.callback = NULL;
    audiospec.userdata = NULL;

    /* open default audio device (allow audio changes) */
    device = SDL_OpenAudioDevice(NULL, 0, &audiospec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    /* ~.5 seconds worth of audio (probably overkill) */
    audio_buffer = (unsigned char*)malloc(SAMPLES_PER_FRAME * 30);

    /* start playing audio */
    SDL_PauseAudioDevice(device, 0);
}

Audio2::~Audio2() {
    /* pause & close the audio */
    SDL_PauseAudioDevice(device, 1);
    if (device) SDL_CloseAudioDevice(device);
    free(audio_buffer);
}

void Audio2::SineWave(int length) {
    for (int i = 0; i < length; i++) {
        /* sine wave varies from 120 - 134 */
        audio_buffer[i] = (unsigned char)((AMPLITUDE * sin(wave_position)) + BIAS);
        wave_position += wave_increment;
    }
}

void Audio2::Beep() {
    if (SDL_GetQueuedAudioSize(device) < (SAMPLES_PER_FRAME * 2)) {
        SineWave(SAMPLES_PER_FRAME);
        SDL_QueueAudio(device, audio_buffer, SAMPLES_PER_FRAME);
    }
}